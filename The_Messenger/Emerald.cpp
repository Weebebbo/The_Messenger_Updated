#include "Emerald.h"
#include "StaticObject.h"
#include "SpriteFactory.h"

using namespace agp;

Emerald::Emerald(Scene* scene, const RectF& rect, int layer) :
	CollidableObject(scene, rect, nullptr, layer)
{
	_compenetrable = true;

	_yGravityForce = 0;
	
	_sprite = SpriteFactory::instance()->get("money");
}

void Emerald::update(float dt)
{
	CollidableObject::update(dt);
}

bool Emerald::collision(CollidableObject* with, bool begin, Direction fromDir) { 

	if (dynamic_cast<Mario*>(with)) {
		std::cout << "ninja prende la moneta" << std::endl;
		this->kill();
		return true; 
	}
	else
		return false; 
}

bool Emerald::collidableWith(CollidableObject* obj)
{
	if (dynamic_cast<Mario*>(obj))
		return true;
}



