#pragma once
#include "CollidableObject.h"

namespace agp
{
	class Crystal;
}

class agp::Crystal : public CollidableObject
{

private:

	int _health;
	bool _didMarioHitMe;
	bool _inLoop;

public:

	Crystal(Scene* scene, const RectF& rect, int layer = 0);
	~Crystal() {};

	virtual void update(float dt) override;

	virtual std::string name() override {
		return strprintf("Crystal[%d]", _id);
	}

	//methods for collision 
	virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
};