#pragma once

#include "KinematicObject.h"

namespace agp
{
	class NinjaLift;
}

class agp::NinjaLift : public KinematicObject
{
protected:

	double _r0, _r1;	// range of movement in absolute y (or x) coordinates
	bool _vertical;		// vertical / horizontal movement

public:

	NinjaLift(Scene* scene, const RectF& rect, Sprite* sprite, bool vertical, float range, int layer = 0);

	virtual void update(float dt) override;

	virtual std::string name() override {
		return strprintf("NinjaLift[%d]", _id);
	}
};