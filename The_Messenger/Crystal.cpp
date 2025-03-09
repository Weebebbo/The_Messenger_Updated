#include "Crystal.h"
#include "StaticObject.h"
#include "SpriteFactory.h"
#include "Sword.h"
#include "Mario.h"

using namespace agp;

Crystal::Crystal(Scene* scene, const RectF& rect, int layer) :
	CollidableObject(scene, rect, nullptr, layer)
{
	_compenetrable = true;
	_fit = false; 
	
	setRect(RectF(12, -0.2f, 3.5f, 5.5f)); 
	_collider.adjust(0.3f, 0.1f, 2.4f, 4.0f); 

	_sprite = SpriteFactory::instance()->get("crystal");

	_yGravityForce = 0;
}

void Crystal::update(float dt)
{
	CollidableObject::update(dt);
}

bool Crystal::collision(CollidableObject* with, bool begin, Direction fromDir) {

	Sword* sword = dynamic_cast<Sword*>(with);

	if (sword != nullptr) {
		this->kill();
		return true;
	}
	else
		return false;
}