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
#include "Bridge.h"
#include "LevelLoader.h"

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

	if (mario->get_hitFromLeft() || mario->get_hitFromRight() || mario->get_hitFromBottom())
		mario->move(Direction::NONE);
	else if (keyboard[SDL_SCANCODE_RIGHT] && !keyboard[SDL_SCANCODE_LEFT])
		mario->move(Direction::RIGHT);
	else if (keyboard[SDL_SCANCODE_LEFT] && !keyboard[SDL_SCANCODE_RIGHT])
		mario->move(Direction::LEFT);
	else if (keyboard[SDL_SCANCODE_LEFT] && keyboard[SDL_SCANCODE_RIGHT])
		mario->move(Direction::NONE);
	else
		mario->move(Direction::NONE);

	// Salto
	if (mario->get_canMarioJumpAgain() && mario->get_iWantToJumpAgain())
	{
		mario->jump(keyboard[SDL_SCANCODE_SPACE]);
		mario->set_canMarioJumpAgain(false);
	}
	else if (!mario->get_canMarioJumpAgain())
	{
		mario->set_iWantToJumpAgain(false);
		mario->jump(keyboard[SDL_SCANCODE_SPACE]);
	}
	else
		mario->jump(keyboard[SDL_SCANCODE_SPACE]);

	mario->crouch(keyboard[SDL_SCANCODE_DOWN]);
	if (mario->get_crouch() && keyboard[SDL_SCANCODE_Z])
		mario->descend();

	if (mario->get_wantsToClimb() || (!mario->get_wantsToClimb() && mario->get_climbingMovement()))
	{
		if (!mario->get_finishedClimbingWallUpperLimit() && !mario->get_finishedClimbingWallLowerLimit())
		{
			if (keyboard[SDL_SCANCODE_UP] && !keyboard[SDL_SCANCODE_SPACE])
			{
				mario->move(Direction::NONE);
				mario->setVelY(-5);
				mario->climbing_movement();
			}
			else if (keyboard[SDL_SCANCODE_DOWN] && !keyboard[SDL_SCANCODE_SPACE])
			{
				mario->move(Direction::NONE);
				mario->setVelY(3);
				mario->climbing_movement();
			}
			else
				goto end;
		}

		else if (mario->get_finishedClimbingWallUpperLimit())
		{
			if (keyboard[SDL_SCANCODE_UP])
			{
				mario->move(Direction::NONE);
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
				mario->move(Direction::NONE);
				mario->setVelY(-0.9f);
				mario->climbing_movement();
			}
			else
				mario->set_finishedClimbingWallLowerLimit(false);
		}
		else
		{
		end:
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

	// Movimento della camera in base a dove sta Mario nella stanza
	if (LevelLoader::instance()->get_marioInRoom() == 0)
		_view->setRect(RectF(0, 6, 20, 18));
	else if (LevelLoader::instance()->get_marioInRoom() == 1 && !LevelLoader::instance()->get_room1StopCamera())
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 2.5);
	else if (LevelLoader::instance()->get_marioInRoom() == 2)
	{
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 2.5);
		_view->setY(35);
	}
	else if (LevelLoader::instance()->get_room1StopCamera())
		_view->setRect(RectF(141.5f, 6, 20, 18));

	//_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);
	//_view->setY(mario->rect().pos.y - _view->rect().size.y / 2 + 1.5);
}

void PlatformerGameScene::event(SDL_Event& evt)
{
	GameScene::event(evt);

	Mario* mario = dynamic_cast<Mario*>(_player);

	if (evt.type == SDL_KEYDOWN && (evt.key.keysym.scancode == SDL_SCANCODE_RETURN || evt.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
		Game::instance()->pushScene(Menu::pauseMenu());
	else if ((evt.type == SDL_KEYDOWN && evt.key.keysym.scancode == SDL_SCANCODE_A) && !mario->get_damageSkid())
		mario->attack();

	if (evt.type == SDL_KEYDOWN && evt.key.keysym.scancode == SDL_SCANCODE_SPACE && mario->get_canMarioJumpAgain())
		mario->set_iWantToJumpAgain(true);
}