// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Trigger.h"
#include "Mario.h"
#include "PlatformerGameScene.h"

using namespace agp;

Trigger::Trigger(Scene* scene, const RectF& rect, CollidableObject* watched, std::function<void()> task) :
	CollidableObject(scene, rect, nullptr)
{
	_task = task;
	_watched = watched;
	_compenetrable = true;

	_transitioning = false;
}

void Trigger::update(float dt)
{
	RenderableObject::update(dt);

	//NOTA: LO SPESSORE DEI TRIGGER DEVE NECESSARIAMENTE ESSERE DI 0.1F, SIA VERTICALE SIA ORIZZONTALE
	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());
	if (this->distance(mario) > 2.5f)
	{
		_transitioning = false;
	}
}

// extends logic collision (+trigger behavior)
bool Trigger::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	{
		if (with == _watched && !_transitioning)
		{
			_task();
			_transitioning = true;
			return true;
		}
		else
		{
			return false;
		}
	}
}