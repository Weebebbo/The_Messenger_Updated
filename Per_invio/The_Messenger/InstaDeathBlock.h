// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "CollidableObject.h"

namespace agp
{
	class InstaDeathBlock;
}

// StaticObject class.
// - provides base class for all objects that do not generally update physics
//   nor detect/resolve collisions
class agp::InstaDeathBlock : public CollidableObject
{

protected:


public:

	InstaDeathBlock(Scene* scene, const RectF& rect, Sprite* sprite, int layer = 0);
	virtual ~InstaDeathBlock() {}

	// extends game logic (-physics, -collisions)
	virtual void update(float dt) override { RenderableObject::update(dt); }

	virtual bool collidableWith(CollidableObject* obj) override;
	virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;

	virtual std::string name() override {
		return strprintf("StaticLift[%d]", _id);
	}
};