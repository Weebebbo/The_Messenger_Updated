// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "HUD.h"
#include "SpriteFactory.h"
#include "View.h"
#include "Game.h"
#include "PlatformerGameScene.h"
#include "Mario.h"

using namespace agp;

HUD::HUD()
	: UIScene(RectF(0, 0, 16, 15), { 16, 16 })
{
	setBackgroundColor(Color(0, 0, 0, 0));

	_score = 0;
	_coins = 0;
	_world = 1;
	_level = 1;
	_time = 400;
	_fps = 0;

	new RenderableObject(this, RectF(0.5, 0.5, 2.5, 0.5), SpriteFactory::instance()->getText("ALEXBRIA", {0.3f, 0.3f}));
	//new RenderableObject(this, RectF(5.5, 0.5, 2, 0.5), SpriteFactory::instance()->getText("DIO", { 0.5f, 0.5f }));
	//new RenderableObject(this, RectF(9.0, 0.5, 2.5, 0.5), SpriteFactory::instance()->getText("WORLD", { 0.5f, 0.5f }));
	//new RenderableObject(this, RectF(12.5, 0.5, 2, 0.5), SpriteFactory::instance()->getText("TIME", { 0.5f, 0.5f }));
	//new RenderableObject(this, RectF(6.0, 1, 0.5, 0.5), SpriteFactory::instance()->getText("*", { 0.5f, 0.5f }));
	//new RenderableObject(this, RectF(10, 1, 0.5, 0.5), SpriteFactory::instance()->getText("-", { 0.5f, 0.5f }));

	for (int i = 0; i < 5; i++)
		_healthBar[i] = new RenderableObject(this, RectF(0.5 + i * 0.5, 0.7, 0.5, 1.1), SpriteFactory::instance()->get("hud_health_bar"));

	_fpsObj = new RenderableObject(this, RectF(6.5, -4, 2, 0.5), SpriteFactory::instance()->getText(std::to_string(_fps), {0.5f, 0.5f}));
	//_scoreObj = new RenderableObject(this, RectF(1.5, 1, 3, 0.5), SpriteFactory::instance()->getText(std::to_string(_score), { 0.5f, 0.5f }, 6, '0'));
	_flashingCoinObj = new RenderableObject(this, RectF(14.6, 0.5, 0.8, 1), SpriteFactory::instance()->get("hud_gem"));
	_coinsObj = new RenderableObject(this, RectF(13.5, 0.7, 1, 0.5), SpriteFactory::instance()->getText(std::to_string(_coins), { 0.5f, 0.5f }, 2, '0'));
	//_worldObj = new RenderableObject(this, RectF(9.5, 1, 0.5, 0.5), SpriteFactory::instance()->getText(std::to_string(_world), { 0.5f, 0.5f }));
	//_levelObj = new RenderableObject(this, RectF(10.5, 1, 0.5, 0.5), SpriteFactory::instance()->getText(std::to_string(_level), { 0.5f, 0.5f }));
	_timeObj = new RenderableObject(this, RectF(13, -4, 1.5, 0.5), SpriteFactory::instance()->getText(std::to_string(int(round(_time))), { 0.5f, 0.5f }, 3, '0'));

	// setup view (specific for super mario bros)
	_view = new View(this, _rect);
	_view->setFixedAspectRatio(Game::instance()->aspectRatio());
	_view->setRect(RectF(0, 0, 16, 15));
}

// extends update logic (+time management)
void HUD::update(float timeToSimulate)
{
	UIScene::update(timeToSimulate);

	if (!_active)
		return;
	
	int timePrev = int(round(_time));
	_time -= timeToSimulate;
	int timeCurr = int(round(_time));
	if(timePrev != timeCurr)
		_timeObj->setSprite(SpriteFactory::instance()->getText(std::to_string(timeCurr), { 0.5f, 0.5f }, 3, '0'), true);

	setFPS(Game::instance()->currentFPS());
}

void HUD::setFPS(int fps) 
{ 
	if (fps != _fps)
	{
		_fps = fps;
		_fpsObj->setSprite(SpriteFactory::instance()->getText(std::to_string(_fps), { 0.5f, 0.5f }), true);
	}
}

void HUD::addCoin()
{
	
	int coins = get_coins();
	coins++; 
	set_coins(coins); 
	
	_coinsObj->kill();
	_coinsObj = new RenderableObject(this, RectF(13.5, 0.7, 1, 0.5), SpriteFactory::instance()->getText(std::to_string(coins), { 0.5f, 0.5f }, 2, '0'));
}

void HUD::healthBarDown(int& iterator)
{
	_healthBar[iterator + 1]->kill();
	_healthBar[iterator + 1] = new RenderableObject(this, RectF(0.5 + (iterator + 1) * 0.5, 0.8, 0.5, 1.2), SpriteFactory::instance()->get("hud_health_bar2"));
}

void HUD::healthBarUp(int& iterator, Mario* mario)
{
	_healthBar[iterator + 1]->kill();
	_healthBar[iterator + 1] = new RenderableObject(this, RectF(0.5 + (iterator + 1) * 0.5, 0.7, 0.5, 1.1), SpriteFactory::instance()->get("hud_health_bar"));
	mario->set_didMarioHitPotion(false);
}