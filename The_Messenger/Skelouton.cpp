#include "HammerBrother.h"
#include "SpriteFactory.h"
#include "Hammer.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "Skelouton.h"
#include <random>

using namespace agp;

Skelouton::Skelouton(Scene* scene, const PointF& pos)
	: Enemy(scene, RectF(pos.x + 1 / 16.0f, pos.y - 1, 0.5f, 1.5f), SpriteFactory::instance()->get("skelouton_stand"))
{
	// Bria pensaci tu
	//_collider.adjust(0.3f, -0.9f, 1.2f, -0.1f);
	//_collider = { 0.2f, -0.5f, 1.5f, 2 };
	_collider.adjust(0.1f, 0.4f, -0.1f, -1 / 16.0f);
	_fit = false;

	_pivot = pos;
	_throwing = false;
	_chasing = false;

	_stand = true; //appena viene spawnato lo scheletro è fermo
	_emerging = false;
	_walk = false;
	_fit = false;

	_state = 0;

	_sprites["walk_on"] = SpriteFactory::instance()->get("skelouton_walk_on");
	_sprites["walk"] = SpriteFactory::instance()->get("skelouton_walk");

	// default physics
	_yGravityForce = 25;
	_xMoveForce = 0;
	_xFrictionForce = 0;
	_xSkiddingForce = 1000;
	_xVelMax = 1;
	_xDir = Direction::LEFT;
	_halfRangeX = 0.7f;

	schedule("emerging_on", 2.0f, [this] {
		_emerging = true;
		_state = 1;
		schedule("walk_on", 0.5f, [this] { _state = 2; });
		}); 

}

void Skelouton::update(float dt)
{
	Enemy::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	//std::cout << "stand:" << _stand << std::endl; 
	//std::cout << "walk:" << _walk << std::endl;
	//std::cout << "emerging: " << _emerging << std::endl;

	//std::cout << mario->pos().y << std::endl;
	//std::cout << this->pos().y << std::endl;

	switch (_state) {
	case 0:
		break;
	case 1:
		_sprite = _sprites["walk_on"]; 
		//setRect(RectF(pos().x, pos().y, 2, 2));
		//_collider = { 0.35, -1.52, 1.25, 2.05 };
		break;
	case 2:
		_sprite = _sprites["walk"]; 
		_xMoveForce = 1000;
		move(Direction::LEFT);

		break; 
	default:
		std::cout << "non succede un cazzo" << std::endl; 
	}
	
				
	/*if (_walk) {
		_sprite = _sprites["walk"]; 
		_xMoveForce = 1000;
		move(Direction::LEFT); 
	}*/
		
	//_facingDir = Direction::NONE;
	//_xDir = Direction::NONE;
	//_vel.x = 0;
	//return;


}

bool Skelouton::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(with);

	if (mario) {
		std::cout << "collisione rilevata" << std::endl; 
		return true;
	}

	return false;
}