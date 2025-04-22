#include "InstaDeathBlock.h"
#include "Mario.h"

using namespace agp;

InstaDeathBlock::InstaDeathBlock(Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
	CollidableObject(scene, rect, sprite, layer)
{
	_compenetrable = true;
}

bool InstaDeathBlock::collidableWith(CollidableObject* obj)
{
	if (dynamic_cast<Mario*>(obj))
		return true;
	else
		return false;
}

bool InstaDeathBlock::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(with);

	if (mario)
	{
		if (mario->sceneCollider().top() > sceneCollider().top())
		{
			mario->die();
			return true;
		}

	}
	else
		return false;
}