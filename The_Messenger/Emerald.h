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

	// Mi serve per quando li spawno dopo aver colpito il candelabro
	// La funzione gli da delle velocità randomiche e poi li stoppa dopo qualche secondo
	void randomMove();

	//methods for collision 
	virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
	virtual bool collidableWith(CollidableObject* obj) override;
};