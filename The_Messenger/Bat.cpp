#include "HammerBrother.h"
#include "SpriteFactory.h"
#include "Hammer.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "Bat.h"
#include "StaticObject.h"
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
	_compenetrable = false;

	// default physics
	_yGravityForce = 0;
	_xMoveForce = 0;
	_xFrictionForce = 1000;
	_xSkiddingForce = 1000;
	_xVelMax = 2;
	_xDir = Direction::LEFT;
	_halfRangeX = 0.7f;

}

void Bat::update(float dt)
{
	Enemy::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	// il controllo sulle coordinate viene fatto solo per l'attivazione, dopodiche lo stronzo segue mario per tutta la mappa
	if (mario->pos().x < this->pos().x && mario->pos().x > this->pos().x - 3) {
		_chasing = true;
	} 

	if (_chasing) {
		_flying = true;
		_sprite = _sprites["flying"];
		_xMoveForce = 1000;
		_yGravityForce = 2; 


		if (mario->pos().x < this->pos().x)
			move(Direction::LEFT);
		else if (mario->pos().x > this->pos().x)
			move(Direction::RIGHT);
		else
			move(Direction::NONE);

		if (mario->pos().y < this->pos().y)
			_yGravityForce = -2; 

		LineF downRay = {
			sceneCollider().bl(),
			sceneCollider().bl() + PointF(0, 0.5f)
		};

		//RAYCAST DI BRIA MORTO ESPLOSO PER EVITARE CHE IL PIPISTRONZO SBATTA A TERRA COME UN DOWN 
		float hitTimes;
		if (dynamic_cast<StaticObject*>(scene()->raycastNearest(downRay, hitTimes))) {
			setVelY(-1);
		}

		if (_vel.x > 0) // x-mirroring
			_flip = SDL_FLIP_HORIZONTAL;
		else
			_flip = SDL_FLIP_NONE;

	}
}