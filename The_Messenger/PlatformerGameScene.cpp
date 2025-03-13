// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "PlatformerGameScene.h"
#include "View.h"
#include "Mario.h"
#include "Menu.h"
#include "Game.h"
#include "timeUtils.h"
#include "HUD.h"
#include "PlatformerGame.h"
#include "geometryUtils.h"
#include "StaticLift.h"

using namespace agp;

PlatformerGameScene::PlatformerGameScene(const RectF& rect, const Point& pixelUnitSize, float dt)
	: GameScene(rect, pixelUnitSize, dt)
{
	// NES aspect ratio (16 x 15)
	_view->setRect(RectF(0, -12, 20, 18));
}

void PlatformerGameScene::updateControls(float timeToSimulate)
{
	if (_cameraManual)
		return;

	Mario* mario = dynamic_cast<Mario*>(_player);
	const Uint8* keyboard = SDL_GetKeyboardState(0);

	if (keyboard[SDL_SCANCODE_RIGHT] && !keyboard[SDL_SCANCODE_LEFT])
		mario->move(Direction::RIGHT);
	else if (keyboard[SDL_SCANCODE_LEFT] && !keyboard[SDL_SCANCODE_RIGHT])
		mario->move(Direction::LEFT);
	else if (keyboard[SDL_SCANCODE_LEFT] && keyboard[SDL_SCANCODE_RIGHT])
		mario->move(Direction::NONE);
	else
		mario->move(Direction::NONE);

	mario->jump(keyboard[SDL_SCANCODE_SPACE]);
	mario->crouch(keyboard[SDL_SCANCODE_DOWN]);
	if (mario->get_crouch() && keyboard[SDL_SCANCODE_Z])
	{
		mario->descend();
		mario->get_collisionWithLift();
	}

	if (mario->get_wantsToClimb() || (!mario->get_wantsToClimb() && mario->get_climbingMovement()))
	{
		if (keyboard[SDL_SCANCODE_UP] && !mario->get_finishedClimbingWallUpperLimit() && !mario->get_finishedClimbingWallLowerLimit())
		{
			mario->setVelY(-5);
			mario->climbing_movement();
		}
		else if (keyboard[SDL_SCANCODE_DOWN] && !mario->get_finishedClimbingWallUpperLimit() && !mario->get_finishedClimbingWallLowerLimit())
		{
			mario->setVelY(3);
			mario->climbing_movement();
		}
		else if (mario->get_finishedClimbingWallUpperLimit())
		{
			if (keyboard[SDL_SCANCODE_UP])
			{
				mario->setVelY(-0.9f);
				mario->climbing_movement();
			}
			else 
				mario->set_finishedClimbingWallUpperLimit(false);
		}
		else if (mario->get_finishedClimbingWallLowerLimit())
		{
			if (keyboard[SDL_SCANCODE_DOWN])
			{
				mario->setVelY(-0.9f);
				mario->climbing_movement();
			}
			else
				mario->set_finishedClimbingWallLowerLimit(false);
		}
		else
		{
			mario->set_climbingMovement(false);
			mario->set_wantsToClimb(true);
		}
	}
}

void PlatformerGameScene::updateCamera(float timeToSimulate)
{
	if (_cameraManual)
	{
		GameScene::updateCamera(timeToSimulate);
		return;
	}

	Mario* mario = dynamic_cast<Mario*>(_player);
	_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);
}

void PlatformerGameScene::event(SDL_Event& evt)
{
	GameScene::event(evt);

	Mario* mario = dynamic_cast<Mario*>(_player);

	if (evt.type == SDL_KEYDOWN && (evt.key.keysym.scancode == SDL_SCANCODE_RETURN || evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
		Game::instance()->pushScene(Menu::pauseMenu());
	else if (evt.type == SDL_KEYDOWN && evt.key.keysym.scancode == SDL_SCANCODE_A)
		mario->attack();
}