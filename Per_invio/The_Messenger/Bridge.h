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
	class Bridge;
}

// StaticObject class.
// - provides base class for all objects that do not generally update physics
//   nor detect/resolve collisions
class agp::Bridge : public CollidableObject
{

protected:
	

public:

	Bridge(Scene* scene, const RectF& rect, Sprite* sprite, int layer = 0);
	virtual ~Bridge() {}

	// extends game logic (-physics, -collisions)
	virtual void update(float dt) override;
	virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;

	virtual std::string name() override {
		return strprintf("StaticLift[%d]", _id);
	}
};