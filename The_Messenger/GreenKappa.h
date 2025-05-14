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
	class GreenKappa;
}

class agp::GreenKappa : public Enemy
{
private: 
	int _healthBar;
	RectF _limitRect;
	bool _canSwordHitMe;
	bool _prevDidSwordHitMe;
	bool _hitFromLeft;
	bool _hitFromRight; 
	bool _canMarioTakeDamage;
	Uint32 _invincibilityStartGreenKappa;

protected:

	bool _throwing;			// throwing hammer
	bool _chasing;			// chasing Mario
	bool _changeDirection;  // verifica se il coglione deve cambiare direzione
	PointF _pivot;			// center of horizontal movement
	float _halfRangeX;		// half range of horizontal movement
	std::map<std::string, Sprite*> _sprites;

public:

	GreenKappa(Scene* scene, const PointF& pos);

	// extends game logic (+HammerBrother logic)
	virtual void update(float dt) override;

	virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override; 
	virtual std::string name() override { return strprintf("GreenKappa[%d]", _id); }
	virtual void smash() override;
};