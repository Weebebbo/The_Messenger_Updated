#pragma once

#include "CollidableObject.h"
#include "Mario.h"

namespace agp
{
	class Emerald;
}

class agp::Emerald : public CollidableObject
{

private:

public:

	Emerald(Scene* scene, const RectF& rect, int layer = 0);

	virtual void update(float dt) override;

	virtual std::string name() override {
		return strprintf("Emerald[%d]", _id);
	}

	//methods for collision 
	virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
	//virtual bool collidableWith(CollidableObject* obj) override;
};