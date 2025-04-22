#include "HammerBrother.h"
#include "SpriteFactory.h"
#include "Hammer.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "Bat.h"
#include <random>

using namespace agp;

Bat::Bat(Scene* scene, const PointF& pos)
	: Enemy(scene, RectF(pos.x + 1 / 16.0f, pos.y - 1, 1.5f, 1.5f), SpriteFactory::instance()->get("bat_stand"))
{
	_collider.adjust(0.1f, 0.4f, -0.1f, -1 / 16.0f);
	_fit = false;
	_sprites["flying"] = SpriteFactory::instance()->get("bat_flying");

	_pivot = pos;
	_flying = false;
	_throwing = false;
	_chasing = false;

	// default physics
	_yGravityForce = -1000;
	_xMoveForce = 0;
	_xFrictionForce = 1000;
	_xSkiddingForce = 1000;
	_xVelMax = 1;
	_xDir = Direction::LEFT;
	_halfRangeX = 0.7f;

	// scripting (chasing Mario)
	schedule("chasing", 3.0f, [this]
		{
			_chasing = true;
			_xVelMax *= 2;
		});
}

void Bat::update(float dt)
{
	Enemy::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	if (_chasing) {
		_flying = true;
		_sprite = _sprites["flying"]; 
		_xMoveForce = 1000;
		

		if (mario->pos().x < this->pos().x)
			move(Direction::LEFT);
		else if (mario->pos().x > this->pos().x)
			move(Direction::RIGHT);
		else
			move(Direction::NONE);

		if (mario->pos().y > this->pos().y) {
			_yGravityForce = 2;
		}
		else if (mario->pos().y < this->pos().y) {
			_yGravityForce = -2;
		}
		
		if (_vel.x > 0) // x-mirroring
			_flip = SDL_FLIP_HORIZONTAL;
		else
			_flip = SDL_FLIP_NONE;

	}
}