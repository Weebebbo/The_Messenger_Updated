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
	if (LevelLoader::instance()->get_marioInRoom() == 1)
	{
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);
		_view->setY(28.8f);

		if (_view->rect().left() < 0)
			_view->setX(0);
		else if (_view->rect().left() > 140.7f)
			_view->setX(140.7f);
	}
	else if (LevelLoader::instance()->get_marioInRoom() == 2)
	{
		_view->setY(mario->rect().pos.y - _view->rect().size.y / 2 + 1.5);
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);

		if (_view->rect().top() > 9.9f)
			_view->setY(9.9f);
		else if (_view->rect().top() < 6)
			_view->setY(6);

		if (_view->rect().left() > 147.4f)
			_view->setX(147.4f);
		else if (_view->rect().left() < 68)
			_view->setX(68);
	}
	else if (LevelLoader::instance()->get_marioInRoom() == 3)
	{
		_view->setY(mario->rect().pos.y - _view->rect().size.y / 2 + 1.5);
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);
		if (_view->rect().top() > 51)
			_view->setY(51);
		if (_view->rect().left() > 144.5f)
			_view->setX(144.5f);

		if (LevelLoader::instance()->get_room3MoveCamera())
		{
			if (_view->rect().left() < 119)
				_view->setX(119);
			if (_view->rect().top() < 47)
				_view->setY(47);
		}
	}
	else if (LevelLoader::instance()->get_marioInRoom() == 4)
	{
		_view->setY(mario->rect().pos.y - _view->rect().size.y / 2 + 1.5);
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);

		if (_view->rect().top() > 51)
			_view->setY(51);
		else if (_view->rect().top() < 48)
			_view->setY(48);

		if (_view->rect().left() < 164)
			_view->setX(164);
		else if (_view->rect().left() > 185)
			_view->setX(185);
	}
	else if (LevelLoader::instance()->get_marioInRoom() == 5)
	{
		_view->setY(mario->rect().pos.y - _view->rect().size.y / 2 + 1.5);
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);

		if (_view->rect().top() < 47)
			_view->setY(47);
		else if (_view->rect().top() > 75)
			_view->setY(75);

		if (_view->rect().left() < 205)
			_view->setX(205);
		else if (_view->rect().left() > 232)
			_view->setX(232);
	}
	else if (LevelLoader::instance()->get_marioInRoom() == 6)
	{
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);
		_view->setY(49.5f);
		
		if (_view->rect().left() < 252)
			_view->setX(252);
		else if (_view->rect().left() > 296)
			_view->setX(296);
	}
	else if (LevelLoader::instance()->get_marioInRoom() == 9)
	{
		_view->setY(mario->rect().pos.y - _view->rect().size.y / 2 + 1.5);
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);

		if (_view->rect().top() < 67.2f)
			_view->setY(67.2f);
		else if (_view->rect().top() > 73)
			_view->setY(73);

		if (_view->rect().left() < 302)
			_view->setX(302);
		else if (_view->rect().left() > 398.6f)
			_view->setX(398.6f);
	}
	else if (LevelLoader::instance()->get_marioInRoom() == 10)
	{
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);
		_view->setY(46.5f);
		
		if (_view->rect().left() < 378)
			_view->setX(378);
		else if (_view->rect().left() > 398.6f)
			_view->setX(398.6f);
	}
	else if (LevelLoader::instance()->get_marioInRoom() == 11)
	{
		_view->setX(mario->rect().pos.x - _view->rect().size.x / 2 + 1.5);
		_view->setY(28.3f);
		
		if (_view->rect().left() < 324)
			_view->setX(324);
		else if (_view->rect().left() > 369.4f)
			_view->setX(369.4f);
	}
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