#include "Water.h"
#include "Mario.h"
#include "PlatformerGameScene.h"

using namespace agp;

Water::Water(Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
	CollidableObject(scene, rect, sprite, layer)
{
	_compenetrable = true;
	_didMarioHitMe = false;
}

void Water::update(float dt)
{
	RenderableObject::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());
	if (mario->sceneCollider().bottom() < rect().top() && _didMarioHitMe)
	{
		mario->set_isSwimming(false);
		mario->set_rise(true);
		mario->setVelY(-20);
		_didMarioHitMe = false;
	}
}

bool Water::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(with);

	if (mario && !_didMarioHitMe)
	{
		mario->set_isSwimming(true);
		_didMarioHitMe = true;
		return true;
	}
	else
		return false;
}