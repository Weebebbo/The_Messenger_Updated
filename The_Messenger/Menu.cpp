// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Menu.h"
#include "SpriteFactory.h"
#include "View.h"
#include "Game.h"
#include "Window.h"
#include "Audio.h"
#include "LevelLoader.h"
#include "Mario.h"

using namespace agp;

bool MUSIC = true; 

MenuItem::MenuItem(Menu* container, int index, const std::string& text, std::function<void()> task)
	: RenderableObject(container, 
		RectF(
			container->menuRect().left() + 0.6f, 
			container->menuRect().top() + 0.1f + 0.7f * index, 
			container->menuRect().size.x, 0.5f),
		SpriteFactory::instance()->getText(' ' + text, { 0.5f, 0.5f }, 0, ' ', false), 1)
{
	_container = container;
	_index = index;
	_text = text;
	_task = task;
	_selected = false;
	_focusColor = { 0, 0, 0, 0 }; //tolgo il colore di selezione
}

void MenuItem::refresh()
{
	setSprite(SpriteFactory::instance()->getText(' ' + _text, { 0.5f + _selected/30.0f, 0.5f + _selected / 30.0f }, 0, ' ', _selected), true);
}

void MenuItem::update(float dt)
{
	RenderableObject::update(dt);

	_focused = _selected;

}

Menu::Menu(const PointF& position, float width, Menu* parent, bool closable, Color backgroundColor)
	: UIScene(RectF(0, 0, 16, 15), { 16,16 })
{
	_parent = parent;
	_itemSelected = 0;
	_menuRect = { position.x, position.y, width, 0.5f };
	_closable = closable;

	// menu layer
	_menuBackground = new RenderableObject(this, _menuRect, backgroundColor);
	//_rectPositionY = position.y + 0.8f;
	// default: modal menu (blocks all lower scenes)
	_blocking = true;
	// setup view (NES aspect ratio)
	_view->setFixedAspectRatio(Game::instance()->aspectRatio());

	//_music = true;
}

Menu::Menu(Menu* parent)
	: Menu(parent->menuRect().tl(), parent->menuRect().size.x, parent)
{
	_view->setFixedAspectRatio(Game::instance()->aspectRatio());
	_view->setRect(RectF(0, 0, 16, 15));
}

MenuItem* Menu::addItem(const std::string& text, std::function<void()> task)
{
	MenuItem* item = new MenuItem(this, int(_items.size()), text, task);
	_items.push_back(item);
	if (_items.size() == 1)
		item->setSelected(true);

	_menuRect.size.y = -0.2f + _items.size() * 0.6f + 0.5f;
	_menuBackground->setRect(_menuRect);

	return item;
}

void Menu::event(SDL_Event& evt)
{
	UIScene::event(evt);

	if (evt.type == SDL_KEYDOWN)
	{
		if (evt.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			//Audio::instance()->playSound("fireball");
			_items[_itemSelected]->setSelected(false);
			_itemSelected = (_itemSelected + 1) % int(_items.size());
			_items[_itemSelected]->setSelected(true);
		}
		else if (evt.key.keysym.scancode == SDL_SCANCODE_UP)
		{
			//Audio::instance()->playSound("fireball");
			_items[_itemSelected]->setSelected(false);
			_itemSelected = (_itemSelected - 1) < 0 ? int(_items.size()) - 1 : _itemSelected - 1;
			_items[_itemSelected]->setSelected(true);
		}
		else if (evt.key.keysym.scancode == SDL_SCANCODE_RETURN || evt.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			Audio::instance()->playSound("kick");
			_items[_itemSelected]->run();
		}
		else if (_closable && (evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE || evt.key.keysym.scancode == SDL_SCANCODE_LEFT))
		{
			Audio::instance()->playSound("smash");
			Game::instance()->popSceneLater();
		}
	}
}

Menu* Menu::mainMenu()
{
	Menu* menu = new Menu({ 5.0, 10.7 }, 6.0, nullptr, false, Color(0, 0, 0, 0));

	new RenderableObject(menu, RectF(0, 2, 16, 13), SpriteFactory::instance()->get("welcome"), -1);

	menu->addItem("", [menu]()
		{
			Menu* nestedMenu = new Menu(menu);

			nestedMenu->addItem("New Game", [nestedMenu]()
				{
					Game::instance()->popSceneLater();
					Game::instance()->popSceneLater();

					if (MUSIC)
						Audio::instance()->playMusic("mainTheme");
				});

			nestedMenu->addItem("Options", [nestedMenu]() {

				Menu* optionsMenu = new Menu(nestedMenu);
				
				optionsMenu->addItem("Commands", [nestedMenu, optionsMenu]() {
					std::cout << "Fatti in culo!" << std::endl;
					new RenderableObject(optionsMenu, RectF(0, 2, 16, 13), SpriteFactory::instance()->get("commands"), -1);
					});
				
				optionsMenu->addItem(optionsMenu->get_itemTextInvincible(), [nestedMenu, optionsMenu]() {
					dynamic_cast<Mario*>(dynamic_cast<GameScene*>(Game::instance()->scene())->player())->toggleInvincible();
					optionsMenu->itemAt(1)->setText(optionsMenu->get_itemTextInvincible());
					});
				
				optionsMenu->addItem(nestedMenu->get_itemTextVolume(), [nestedMenu, optionsMenu]() {
					dynamic_cast<Menu*>(nestedMenu)->toggleMusic();
					if (MUSIC)
						optionsMenu->itemAt(2)->setText("volume on");
					else
						optionsMenu->itemAt(2)->setText("volume off");
					});
				
				Game::instance()->pushScene(optionsMenu);
				});
			
			nestedMenu->addItem("Quit", []() {Game::instance()->quit(); });

			Game::instance()->pushScene(nestedMenu);
		});

	return menu;
}


Menu* Menu::pauseMenu()
{
	Menu* menu = new Menu({ 5.0, 7.0 }, 6, 0, false);
	new RenderableObject(menu, RectF(0, 0, 16, 17), SpriteFactory::instance()->get("commands"), -1);

	menu->addItem("Resume", []() 
		{
			if (!MUSIC)
				Audio::instance()->haltMusic();
			else
				Audio::instance()->playMusic("mainTheme"); 

			Game::instance()->popSceneLater(); 
			Audio::instance()->resumeMusic();
		});
	
	menu->addItem("Reset", []()
		{
			Game::instance()->reset();
			LevelLoader::instance()->LLReset();
		});
	
	menu->addItem(menu->get_itemTextInvincible(), [menu]() {
		dynamic_cast<Mario*>(dynamic_cast<GameScene*>(Game::instance()->scene())->player())->toggleInvincible();
		menu->itemAt(2)->setText(menu->get_itemTextInvincible());
		});

	menu->addItem(menu->get_itemTextVolume(), [menu]() {
		menu->toggleMusic();
		if (MUSIC)
			menu->itemAt(3)->setText("volume on");
		else
			menu->itemAt(3)->setText("volume off");
		});

	menu->addItem("Quit", []() {Game::instance()->quit(); });

	Audio::instance()->playSound("pause");
	Audio::instance()->pauseMusic();

	return menu;
}

void Menu::toggleMusic() {
	
	if (MUSIC)
		MUSIC = false;
	else 
		MUSIC = true;

	std::cout << MUSIC << std::endl;
}

std::string Menu::get_itemTextVolume() {
	if (MUSIC)
		return "volume on";
	else
		return "volume off";
}

std::string Menu::get_itemTextInvincible() {
	if (dynamic_cast<Mario*>(dynamic_cast<GameScene*>(Game::instance()->scene())->player())->invincible())
		return "godmode on";
	else
		return "godmode off"; 
}

