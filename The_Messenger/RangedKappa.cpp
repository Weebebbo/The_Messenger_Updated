#include "HammerBrother.h"
#include "SpriteFactory.h"
#include "Hammer.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "RangedKappa.h"
#include "Fireball.h"
#include <random>

using namespace agp;

RangedKappa::RangedKappa(Scene* scene, const PointF& pos)
	: Enemy(scene, RectF(pos.x - 1, pos.y - 3, 2.5f, 2.68f), SpriteFactory::instance()->get("ranged_kappa_stand"))
{
	//_collider.adjust(0.1f, 0.4f, -0.1f, -1 / 16.0f);
	_collider = { 0.25, 0.4, 2.05, 2.15 };

	_sprites["ranged_kappa_stand"] = SpriteFactory::instance()->get("ranged_kappa_stand");
	_sprites["ranged_kappa_fireball"] = SpriteFactory::instance()->get("ranged_kappa_fireball");

	_pivot = pos;
	_throwing = false;
	_canThrow = false;
	_chasing = false;

	// default physics
	_yGravityForce = 25;
	_xMoveForce = 0;
	_xFrictionForce = 0;
	_xSkiddingForce = 1000;
	_xVelMax = 1;
	_xDir = Direction::LEFT;
	_halfRangeX = 0.7f;

	schedule("throw_fireball_sprite", 2.0f, [this] {
		if (_canThrow) {
			_throwing = true;
			schedule("throw_fireball_attack1", 0.25f, [this] {
				new Fireball(_scene, rect().tl() + PointF(0, 0.85f), this);
				schedule("throw_fireball_attack2", 0.5f, [this] {
					new Fireball(_scene, rect().tl() + PointF(0, 0.85f), this);
					});
				});
			schedule("throwing_off", 1.0f, [this]() {_throwing = false; });
		}
		}, -1);

	/*schedule("attack", 3.0f, [this] {
		if (_canThrow) {
			_throwing = true;

			schedule("spawn_fireball1", 0.25f, [this] {
				new Fireball(_scene, rect().tl() + PointF(0, 0.85f), this);
				schedule("stop_animation1", 0.25f, [this] { _throwing = false; }); 	
				});

			schedule("start_animation2", 1.0f, [this] {
				_throwing = true;
				schedule("spawn_fireball2", 0.25f, [this] {
					new Fireball(_scene, rect().tl() + PointF(0, 0.85f), this);
					schedule("stop_animation2", 0.25f, [this] { _throwing = false; }); });
				});
		}
	}, -1); */
}

void RangedKappa::update(float dt)
{
	Enemy::update(dt);

	//std::cout << _throwing << std::endl; 

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	//std::cout << _canThrow << std::endl; 
	//std::cout << "Mario: " << mario->pos().x << std::endl;
	//std::cout << "Enemy: " << this->pos().x << std::endl;

	if (mario->pos().x < this->pos().x) {
		_canThrow = true;
	}
	else {
		_canThrow = false;
	}

	if (_throwing)
		_sprite = _sprites["ranged_kappa_fireball"];
	else
		_sprite = _sprites["ranged_kappa_stand"];

}
