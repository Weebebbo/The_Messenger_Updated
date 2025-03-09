// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include "Enemy.h"
#include <map>
#include <string>

namespace agp
{
	class Skelouton;
}

class agp::Skelouton: public Enemy
{
protected:

	bool _throwing;			// throwing hammer
	bool _chasing;			// chasing Mario
	
	//stati del coglione
	bool _stand;			// stato di stand
	bool _emerging;			// stato di passaggio da stand a walk	
	bool _walk;				// stato di walk

	int _state; 

	PointF _pivot;			// center of horizontal movement
	float _halfRangeX;		// half range of horizontal movement
	std::map<std::string, Sprite*> _sprites;

public:

	Skelouton(Scene* scene, const PointF& pos);

	// extends game logic (+HammerBrother logic)
	virtual void update(float dt) override;
	bool collision(CollidableObject* with, bool begin, Direction fromDir) override; 

	virtual std::string name() override { return strprintf("Skelouton[%d]", _id); }
};