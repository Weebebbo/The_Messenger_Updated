// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "StaticObject.h"
#include "Scene.h"
#include "Bridge.h"

#include "GreenKappa.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "RangedKappa.h"

using namespace agp;

Bridge::Bridge(Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
	CollidableObject(scene, rect, sprite, layer)
{

}

void Bridge::update(float dt) {
	
	RenderableObject::update(dt);
}

bool Bridge::collision(CollidableObject* with, bool begin, Direction fromDir) {
	Mario* mario = dynamic_cast<Mario*>(with);

	if (mario)
	{
		if (fromDir == Direction::DOWN || fromDir == Direction::LEFT || fromDir == Direction::RIGHT) {
			_compenetrable = true;

			schedule("compenetrable_off", 0.4f, [this] {
				_compenetrable = false;
				}, 0);

			return true;
		}
		else if (fromDir == Direction::UP) {

			mario->set_collisionWithLift(true); //check collisione con la piattaforma (per annullare il salto)

			if (mario->get_canDescend()) {
				_compenetrable = true;

				schedule("compenetrable_off", 0.2f, [this] {
					_compenetrable = false;
					}, 0);

			}
			return true;
		}
		else
		{
			mario->set_collisionWithLift(false);
			mario->set_canDescend(false);
			return false;
		}
	}
}
