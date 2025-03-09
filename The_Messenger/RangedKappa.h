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
	class RangedKappa;
}

class agp::RangedKappa : public Enemy
{
protected:

	bool _throwing;			// lancio fireball attivo 
	bool _canThrow;			// controlla se è possibile lanciare fireball
	bool _chasing;			// chasing Mario
	PointF _pivot;			// center of horizontal movement
	float _halfRangeX;		// half range of horizontal movement
	std::map<std::string, Sprite*> _sprites;

public:

	RangedKappa(Scene* scene, const PointF& pos);

	// extends game logic (+HammerBrother logic)
	virtual void update(float dt) override;
	
	virtual std::string name() override { return strprintf("RangedKappa[%d]", _id); }
};