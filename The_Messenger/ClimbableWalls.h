// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "CollidableObject.h"

namespace agp
{
	class ClimbableWalls;
}

class agp::ClimbableWalls : public CollidableObject
{
protected:

	bool _didMarioHitMe;

public:

	ClimbableWalls(Scene* scene, const RectF& rect, Sprite* sprite, int layer = 0);
	virtual ~ClimbableWalls() {}

	// extends game logic (-physics, -collisions)
	virtual void update(float dt) override; //{RenderableObject::update(dt);}

	virtual std::string name() override {
		return strprintf("StaticObject[%d]", _id);
	}

	virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
};