#include "Hammer.h"
#include "SpriteFactory.h"
#include "Mario.h"
#include "Fireball.h"
#include "Scene.h"
#include "Sword.h"

using namespace agp;

Fireball::Fireball(Scene* scene, const PointF& pos, Enemy* thrower)
	: Enemy(scene, RectF(pos.x, pos.y, 1, 1), SpriteFactory::instance()->get("fireball"))
{
	_collider.adjust(0.2f, 0.2f, -0.2f, -0.2f);
	_fit = false;
	_smashable = true;
	_thrower = thrower;
	_throwing = false;
	_yGravityForce = 0;
	_xFrictionForce = 0;
	_xSkiddingForce = 0;
	_xMoveForce = 1000;
	_xVelMax = 4;
	_xDir = Direction::NONE;

	//Schedule tolto perchè le fireball partono appena vengono spawnate
	_throwing = true;
	_yGravityForce = 0;
	
	if (thrower->facingDir() == Direction::RIGHT) {
		setVelX(1000);
		_flip = SDL_FLIP_HORIZONTAL; 
	}
	else
		setVelX(-1000);

	_xDir = _thrower->facingDir();
	_angularVelocity = 0;
}

void Fireball::update(float dt)
{
	Enemy::update(dt);

	/*if (!_throwing)
		setPos(_thrower->rect().pos + PointF(2 / 16.0f, 0));*/

	/*if (sceneCollider().pos.y > 50) 
		_scene->killObject(this);*/
}

bool Fireball::collidableWith(CollidableObject* obj)
{
	if (dynamic_cast<Mario*>(obj))
		return true;
	else if (dynamic_cast<Sword*>(obj))
		return true;
	else
		return false;
}

bool Fireball::collision(CollidableObject* with, bool begin, Direction fromDir) {

	Mario* mario = dynamic_cast<Mario*>(with); 

	if (mario) {
		_scene->killObject(this);
		mario->hurt();
		return true;
	}
	else if (dynamic_cast<Sword*>(with))
		return true;
	else
		return false;
}

void Fireball::smash() {
	_scene->killObject(this);
}