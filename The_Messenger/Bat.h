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
	class Bat;
}

class agp::Bat : public Enemy
{
protected:

	bool _throwing;			// throwing hammer
	bool _chasing;			// chasing Mario
	bool _flying; 
	PointF _pivot;			// center of horizontal movement
	float _halfRangeX;		// half range of horizontal movement
	std::map<std::string, Sprite*> _sprites;

public:

	Bat(Scene* scene, const PointF& pos);

	// extends game logic (+HammerBrother logic)
	virtual void update(float dt) override;
	virtual void smash() override;

	virtual std::string name() override { return strprintf("Bat[%d]", _id); }
};