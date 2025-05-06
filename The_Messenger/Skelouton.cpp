#include "HammerBrother.h"
#include "SpriteFactory.h"
#include "Hammer.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "Skelouton.h"
#include "StaticObject.h"
#include <random>

using namespace agp;

Skelouton::Skelouton(Scene* scene, const PointF& pos)
	: Enemy(scene, _rect, SpriteFactory::instance()->get("skelouton_stand"), 1)
{
	
	setPos(pos);
	_rect = { pos.x, pos.y - 1.5f, 1.8f, 2.4f };
	defaultCollider();
	_collider.adjust(0.3f, 1.2f, -0.3f, -0.1f); 
	_fit = false;

	_pivot = pos;
	_throwing = false;
	_chasing = false;
	_boost = false; 
	_compenetrable = true;
	_updateCollider = false;
	_offsetCollider = false;

	_state = 0; //indica lo stato in cui si trova lo scheletro
	// 0 -> standing
	// 1 -> emerging
	// 2 -> walking 
	// 3 -> turbo diesel o anche detto pepe al culo 

	_sprites["walk_on"] = SpriteFactory::instance()->get("skelouton_walk_on");
	_sprites["walk"] = SpriteFactory::instance()->get("skelouton_walk");
	_sprites["run"] = SpriteFactory::instance()->get("skelouton_run");

	// default physics
	_yGravityForce = 25;
	_xMoveForce = 0;
	_xFrictionForce = 0;
	_xSkiddingForce = 1000;
	_xVelMax = 1;
	_xDir = Direction::LEFT;
	_halfRangeX = 0.7f;

	_limitRectSkelouton = { 0, 0, 0, 0 };
	_limitRectMario = { 0, 0, 0, 0 };
}

void Skelouton::update(float dt)
{
	Enemy::update(dt);
	
	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	LineF downRayMario = {
		PointF(mario->sceneCollider().center().x, mario->sceneCollider().bottom()),
		PointF(mario->sceneCollider().center().x, mario->sceneCollider().bottom() + 0.1f)
	};
	float hitTimes; //non so a cosa cazzo serve 
	if (dynamic_cast<StaticObject*>(scene()->raycastNearest(downRayMario, hitTimes)))
		_limitRectMario = dynamic_cast<StaticObject*>(scene()->raycastNearest(downRayMario, hitTimes))->rect();

	if (rect().left() <= _limitRectSkelouton.left())
	{
		move(Direction::RIGHT);
		_flip = SDL_FLIP_HORIZONTAL; 
		_collider = _collider + PointF(-0.3f, 0); 
		_offsetCollider = true;
	}
	else if (sceneCollider().right() >= _limitRectSkelouton.right()) 
	{
		move(Direction::LEFT);
		_flip = SDL_FLIP_NONE;
		if (_offsetCollider) {
			_collider = _collider + PointF(0.3f, 0);
			_offsetCollider = false; 
		}
	}

	if (_state == 0) {
		if (mario->pos().x > this->pos().x - 10 && mario->pos().x < this->pos().x + 10) {
			_state = 1;
			elapsed = SDL_GetTicks();
		}
	}
	else if (_state == 1 && SDL_GetTicks() - emergingTime - elapsed > 650) {	 
		_state = 2;
	}

	if (_state == 2 && vel().x != 0 && _limitRectMario.center().y == _limitRectSkelouton.center().y) {
		std::cout << "stato 3 attivo" << std::endl; 
		_state = 3;
	}
	else if (_state == 3 && _limitRectMario.center().y != _limitRectSkelouton.center().y) {
		_state = 2;
		_xVelMax /= 3;
		_boost = false;
	}

	//std::cout << "mario: " << _limitRectMario.center().y << std::endl;
	//std::cout << "scheletro: " << _limitRectSkelouton.center().y << std::endl;
	_limitRectMario = { 0, 0, 0, 0 };
	_limitRectSkelouton = { 0, 0, 0, 0 };

	switch (_state) {
	case 0:
		break;
	case 1:
		_sprite = _sprites["walk_on"]; 
		break;
	case 2:
		if (!_updateCollider) {
			_collider.adjust(0.1f, -1.1f, 0.1f, -0.1f);
			_collider = _collider + PointF(0, 0.1f); 
			_updateCollider = true; //il collider è stato aggiornato
		}
		_sprite = _sprites["walk"]; 
		_xMoveForce = 1000;
		break;
	case 3:
		if (!_boost) {
			_sprite = _sprites["run"]; 
			_xVelMax *= 3;
			_boost = true;
		}
		break; 
	default:
		std::cout << "non succede un cazzo" << std::endl; 
	}
	
}

bool Skelouton::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Enemy::collision(with, begin, fromDir);
	
	StaticObject* obj = dynamic_cast<StaticObject*>(with);
	
	if (obj && fromDir == Direction::DOWN)
	{
		_limitRectSkelouton = obj->rect();
		return true;
	}
	else
		return false;
}
