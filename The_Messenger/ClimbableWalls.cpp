#include "ClimbableWalls.h"
#include "PlatformerGameScene.h"
#include "Mario.h"

using namespace agp;

ClimbableWalls::ClimbableWalls (Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
	CollidableObject(scene, rect, sprite, layer)
{

}

bool ClimbableWalls::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(with);

	if (mario != nullptr && (mario->get_ball() || mario->get_fall() || mario->get_rise()) && (fromDir == Direction::LEFT || fromDir == Direction::RIGHT))
	{
		// Descrizione della azioni da fare se la collisione succede
		if (!mario->get_wantsToClimb())
			mario->set_wantsToClimb(true);

		return true;
	}
	else
		return false;
}
