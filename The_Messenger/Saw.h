#pragma once
#include "CollidableObject.h"

namespace agp
{
	class Saw;
}

class agp::Saw : public CollidableObject
{
private:

	//Path
	RectF _path;
	int _vertice;

public:

	//I vertici si contano da in basso a sinistra in senso antiorario
	Saw(Scene* scene, const RectF& rect, Sprite* sprite, const RectF& path, int vertice = 1, int layer = 0);
	~Saw() {};

	virtual void update(float dt) override;

	virtual std::string name() override {
		return strprintf("Crystal[%d]", _id);
	}

	//methods for collision 
	bool collidableWith(CollidableObject* obj) override;
	virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
};