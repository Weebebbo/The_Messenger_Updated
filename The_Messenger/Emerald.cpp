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

	Mario* mario = dynamic_cast<Mario*>(with); 

	if (mario) {
		std::cout << "ninja prende la moneta" << std::endl;
		this->kill();
		return true; 
	}
	return false; 
}

//bool Emerald::collidableWith(CollidableObject* obj)
//{
//	return dynamic_cast<StaticObject*>(obj);
//}



