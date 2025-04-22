#include "ClimbableWalls.h"
#include "geometryUtils.h"
#include "Mario.h"
#include "PlatformerGameScene.h"

using namespace agp;

ClimbableWalls::ClimbableWalls (Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
	CollidableObject(scene, rect, sprite, layer)
{
	_didMarioHitMe = false;
}

void ClimbableWalls::update(float dt)
{
	RenderableObject::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	if (mario->get_climbingMovement() && _didMarioHitMe)
	{
		if (mario->sceneCollider().top() < sceneCollider().top())
			mario->set_finishedClimbingWallUpperLimit(true);
		else if (mario->sceneCollider().bottom() > sceneCollider().bottom())
			mario->set_finishedClimbingWallLowerLimit(true);
	}

	if (mario->get_walking() && _didMarioHitMe)
	{
		_didMarioHitMe = false;
		mario->set_finishedClimbingWallUpperLimit(false);
		mario->set_finishedClimbingWallLowerLimit(false);
	}
}

bool ClimbableWalls::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(with);

	if (mario != nullptr && (mario->get_ball() || mario->get_fall() || mario->get_rise()) && (fromDir == Direction::LEFT || fromDir == Direction::RIGHT))
	{
		// Descrizione della azioni da fare se la collisione succede
		if (!mario->get_wantsToClimb())
		{
			mario->set_wantsToClimb(true);

			_didMarioHitMe = true;
		}

		return true;
	}
	else
	{
		return false;
	}
}
