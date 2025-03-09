#include "HammerBrother.h"
#include "SpriteFactory.h"
#include "Hammer.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "GreenKappa.h"
#include "StaticObject.h"
#include <random>

using namespace agp;

GreenKappa::GreenKappa(Scene* scene, const PointF& pos)
	: Enemy(scene, RectF(pos.x + 1 / 16.0f, pos.y - 2, 1.8f, 2.5f), SpriteFactory::instance()->get("green_kappa_walk"))
{
	_collider.adjust(0.1f, 0.4f, -0.1f, -1 / 16.0f);

	_pivot = pos;
	_throwing = false;
	_chasing = false;

	// default physics
	_yGravityForce = 25;
	_xMoveForce = 1000;
	_xFrictionForce = 0;
	_xSkiddingForce = 1000;
	_xVelMax = 1;
	_xDir = Direction::LEFT;
	_halfRangeX = 0.7f;
	_changeDirection = false; //false = sinistra, true = destra
}

void GreenKappa::update(float dt)
{
	Enemy::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	if (_changeDirection)
		move(Direction::RIGHT);
	else
		move(Direction::LEFT); 

	// x-mirroring
	if (_vel.x > 0)
		_flip = SDL_FLIP_HORIZONTAL;
	else
		_flip = SDL_FLIP_NONE;
}

bool GreenKappa::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	CollidableObject* _with = dynamic_cast<CollidableObject*>(with);
	Mario* mario = dynamic_cast<Mario*>(with);

	if (_with == mario) {

		if (mario)
		{
			if (_smashable && mario->invincible())
				smash();
			else
				mario->hurt();

			return true;
		}

		return false;
	}

	if (_with && fromDir == Direction::LEFT)
	{
		std::cout << "rilevata collisione a sinistra" << std::endl;
		_changeDirection = true;
		return true;
	}
	else if (_with && fromDir == Direction::RIGHT) {
		std::cout << "rilevata collisione a destra" << std::endl;
		_changeDirection = false;
		return true;
	}

	return false;
}