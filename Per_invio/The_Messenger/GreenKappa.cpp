#include "HammerBrother.h"
#include "SpriteFactory.h"
#include "Hammer.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "GreenKappa.h"
#include "StaticObject.h"
#include "Sword.h"
#include "Audio.h"
#include "Bridge.h"
#include <random>

using namespace agp;

const Uint32 INVINCIBILITY_DURATION_GREEN_KAPPA = 300;

GreenKappa::GreenKappa(Scene* scene, const PointF& pos)
	: Enemy(scene, RectF(pos.x + 1 / 16.0f, pos.y - 2, 1.8f, 2.5f), SpriteFactory::instance()->get("green_kappa_walk"))
{
	_collider.adjust(0.1f, 0.4f, -0.1f, -1 / 16.0f);
	_fit = false;

	_pivot = pos;
	_throwing = false;
	_chasing = false;

	// default physics
	_yGravityForce = 25;
	_xMoveForce = 1;
	_xFrictionForce = 10;
	_xSkiddingForce = 1000;
	_xVelMax = 1;
	_xDir = Direction::LEFT;
	_halfRangeX = 0.7f;
	_changeDirection = false; //false = sinistra, true = destra
	_invincibilityStartGreenKappa = 0;

	_healthBar = 2; //barra della vita 
	_canSwordHitMe = false;
	_prevDidSwordHitMe = false;
	_hitFromLeft = false;
	_hitFromRight = false; 
	_canMarioTakeDamage = false;

	_limitRect = { 0, 0, 0, 0 }; 
}

void GreenKappa::update(float dt)
{
	if (!_limitRect.size.x) {
		LineF downRay = {
		sceneCollider().bl(),
		sceneCollider().bl() + PointF(0, 0.1f)
		};
		float hitTimes;
		if (dynamic_cast<StaticObject*>(scene()->raycastNearest(downRay, hitTimes)))
			_limitRect = dynamic_cast<StaticObject*>(scene()->raycastNearest(downRay, hitTimes))->rect();
		else if (dynamic_cast<Bridge*>(scene()->raycastNearest(downRay, hitTimes)))
			_limitRect = dynamic_cast<Bridge*>(scene()->raycastNearest(downRay, hitTimes))->rect();
	}

	Enemy::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());
	_canMarioTakeDamage = mario->get_canMarioTakeDamage(); 

	if (sceneCollider().left() <= _limitRect.left())
		move(Direction::RIGHT);
	else if (sceneCollider().right() >= _limitRect.right())
		move(Direction::LEFT); 

	// x-mirroring
	if (_vel.x > 0)
		_flip = SDL_FLIP_HORIZONTAL;
	else
		_flip = SDL_FLIP_NONE;

	if (_hitFromLeft)
		_flip = SDL_FLIP_NONE;
	else if (_hitFromRight)
		_flip = SDL_FLIP_HORIZONTAL; 

	if (!_canSwordHitMe && (SDL_GetTicks() - _invincibilityStartGreenKappa > INVINCIBILITY_DURATION_GREEN_KAPPA)) {
		_canSwordHitMe = true;  
		_hitFromLeft = false; 
		_hitFromRight = false;
	}

}

bool GreenKappa::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	CollidableObject* _with = dynamic_cast<CollidableObject*>(with);
	Mario* mario = dynamic_cast<Mario*>(with);
	Sword* sword = dynamic_cast<Sword*>(with); 

	if (mario)
	{
		if (_smashable && mario->invincible())
			smash();
		else
			mario->hurt();

		return true;
	}

	if (!sword) {
		if (_with && fromDir == Direction::LEFT)
		{
			_changeDirection = true;
			return true;
		}
		else if (_with && fromDir == Direction::RIGHT) {
			_changeDirection = false;
			return true;
		}
	}

	if (sword && !_canSwordHitMe) {
		
		if (fromDir == Direction::RIGHT) {
			_hitFromRight = true;
			_xSkiddingForce = 10;
			_xVelMax = 3000;
			velAdd(Vec2Df(-1, -0.5f)); 
			schedule("prova", 0.1f, [this] {
				_xVelMax = 1;
				_xSkiddingForce = 1000;
				}); 
		}
		else if (fromDir == Direction::LEFT) {
			_hitFromLeft = true;
			_xSkiddingForce = 10;
			_xVelMax = 3000;
			velAdd(Vec2Df(1, -0.5f));
			schedule("prova", 0.1f, [this] {
				_xVelMax = 1;
				_xSkiddingForce = 1000;
				});
		}
		return true; 
	}
		
	return false;
}

void GreenKappa::smash() {

	if (_canSwordHitMe) {
		_healthBar--;
		_canSwordHitMe = false;
		_invincibilityStartGreenKappa = SDL_GetTicks(); 
		
		Audio::instance()->playSound("Enemy_hit");
		_sprite = SpriteFactory::instance()->get("hit");
		schedule("kill_object", 0.3f, [this] {
			_sprite = SpriteFactory::instance()->get("green_kappa_walk");
			});
	}

	if (_healthBar < 0) {
		_scene->killObject(this);
	}
}