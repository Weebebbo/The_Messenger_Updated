#include "HammerBrother.h"
#include "SpriteFactory.h"
#include "Hammer.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "RangedKappa.h"
#include "Fireball.h"
#include "Audio.h"
#include <random>

using namespace agp;

RangedKappa::RangedKappa(Scene* scene, const PointF& pos, bool mirror)
	: Enemy(scene, RectF(pos.x - 1, pos.y - 3, 2.5f, 2.68f), SpriteFactory::instance()->get("ranged_kappa_stand"))
{
	//_collider.adjust(0.1f, 0.4f, -0.1f, -1 / 16.0f);
	_collider = { 0.25, 0.4, 2.05, 2.15 };
	_fit = false;

	_sprites["ranged_kappa_stand"] = SpriteFactory::instance()->get("ranged_kappa_stand");
	_sprites["ranged_kappa_fireball"] = SpriteFactory::instance()->get("ranged_kappa_fireball");

	_pivot = pos;
	_throwing = false;
	_canThrow = false;
	_chasing = false;
	_mirror = mirror;	//se è attivo il nemico funziona specchiato 
	_positionSpawnFireball = PointF(0, 0); 

	// default physics
	_yGravityForce = 25;
	_xMoveForce = 0;
	_xFrictionForce = 0;
	_xSkiddingForce = 1000;
	_xVelMax = 1;
	
	if (mirror) {
		_facingDir = Direction::RIGHT;
		_positionSpawnFireball = rect().tr() + PointF(-0.3f, 4.2f); 
	}
	else {
		_facingDir = Direction::LEFT;
		_positionSpawnFireball = rect().tl() + PointF(-0.3f, 4.2f);
	}
		
	
	_halfRangeX = 0.7f;

	schedule("throw_fireball_sprite", 2.0f, [this] {
		if (_canThrow) {
			_throwing = true;
			schedule("throw_fireball_attack1", 0.25f, [this] {
				new Fireball(_scene, _positionSpawnFireball, this);
				schedule("throw_fireball_attack2", 0.5f, [this] {
					new Fireball(_scene, _positionSpawnFireball, this);
					});
				});
			schedule("throwing_off", 1.0f, [this]() {_throwing = false; });
		}
		}, -1);

}

void RangedKappa::update(float dt)
{
	Enemy::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	if (!_mirror) {
		if (mario->pos().x < this->pos().x && mario->pos().x > this->pos().x - 10) {
			_canThrow = true;
		}
		else {
			_canThrow = false;
		}
	}
	else {
		_flip = SDL_FLIP_HORIZONTAL; 
		if (mario->pos().x > this->pos().x && mario->pos().x < this->pos().x + 10) {
			_canThrow = true;
		}
		else {
			_canThrow = false;
		}
	}

	if (_throwing)
	{
		_sprite = _sprites["ranged_kappa_fireball"];
		Audio::instance()->playSound("Fireball");
	}
	else
		_sprite = _sprites["ranged_kappa_stand"];

	if (_dying)
		_canThrow = false;
}
