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

using namespace agp;

MenuItem::MenuItem(Menu* container, int index, const std::string& text, std::function<void()> task)
	: RenderableObject(container, 
		RectF(
			container->menuRect().left() + 0.6f, 
			container->menuRect().top() + 0.2f + 0.7f * index, 
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

Menu::Menu(const PointF& position, float width, Menu* parent, bool closable)
	: UIScene(RectF(0, 0, 16, 15), { 16,16 })
{
	_parent = parent;
	_itemSelected = 0;
	_menuRect = { position.x, position.y, width, 0.5f };
	_closable = closable;

	// menu layer
	_menuBackground = new RenderableObject(this, _menuRect, Color(111, 123, 234, 0));
	//_rectPositionY = position.y + 0.8f;
	// default: modal menu (blocks all lower scenes)
	_blocking = true;

	// setup view (NES aspect ratio)
	_view->setFixedAspectRatio(Game::instance()->aspectRatio());
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

	if (_closable)
		_menuBackground = new RenderableObject(this, _menuRect, Color(223, 109, 21, 255));

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
	Menu* menu = new Menu({ 5.0, 10.7 }, 6.0, 0, false);

	new RenderableObject(menu, RectF(0, 2, 16, 13), SpriteFactory::instance()->get("welcome"), -1);

	menu->addItem("", [menu]()
		{
			Menu* nestedMenu = new Menu(menu);
			nestedMenu->addItem("Options", [nestedMenu]() {
				std::cout << "Comandi" << std::endl;
				Menu* optionsMenu = new Menu(nestedMenu);
				optionsMenu->addItem("Commands", [nestedMenu]() {
					std::cout << "Fatti in culo!" << std::endl;
					});
				optionsMenu->addItem("Commands", []() {
					std::cout << "Fatti in culo!" << std::endl;
					});
				optionsMenu->addItem("Commands", []() {
					std::cout << "Fatti in culo!" << std::endl;
					});
				Game::instance()->pushScene(optionsMenu);
				});
			nestedMenu->addItem("New Game", []()
				{
					Game::instance()->popSceneLater();
					Game::instance()->popSceneLater();
					Audio::instance()->playMusic("mainTheme");
				});
			nestedMenu->addItem("Quit", []() {Game::instance()->quit(); });

			Game::instance()->pushScene(nestedMenu);
		});

	return menu;
}


Menu* Menu::pauseMenu()
{
	Menu* menu = new Menu({ 1.5, 3 }, 5, 0, false);
	menu->addItem("Resume", []() 
		{
			Game::instance()->popSceneLater(); 
			Audio::instance()->resumeMusic();
		});
	menu->addItem("Reset", []()
		{
			Game::instance()->reset();
			LevelLoader::instance()->LLReset();
		});
	menu->addItem("Quit", []() {Game::instance()->quit(); });

	Audio::instance()->playSound("pause");
	Audio::instance()->pauseMusic();

	return menu;
}