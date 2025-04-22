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
#include "StaticLift.h"
#include "PlatformerGameScene.h"
#include "Mario.h"

using namespace agp;

StaticLift::StaticLift(Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
	CollidableObject(scene, rect, sprite, layer)
{
	_fit = false;
}

void StaticLift::update(float dt) {
	RenderableObject::update(dt);

	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());

	//std::cout << mario->get_collisionWithLift() << std::endl; 
}

bool StaticLift::collision(CollidableObject* with, bool begin, Direction fromDir) {
	Mario* mario = dynamic_cast<Mario*>(with);

	if (mario && (fromDir == Direction::DOWN || fromDir == Direction::LEFT || fromDir == Direction::RIGHT)) {
		_compenetrable = true; 

		schedule("compenetrable_off", 0.4f, [this] {
			_compenetrable = false;
			}, 0); 

		std::cout << "il bro sale sul campanile" << std::endl;
		return true;
	}

	if (mario && fromDir == Direction::UP) {
		
		mario->set_collisionWithLift(true); //check collisione con la piattaforma (per annullare il salto)

		if (mario->get_canDescend()) {
			_compenetrable = true;

			schedule("compenetrable_off", 0.4f, [this] {
				_compenetrable = false;
				}, 0);

			std::cout << "il bro scende dal campanile" << std::endl;
		}
		return true;
	}
	
	mario->set_collisionWithLift(false);
	mario->set_canDescend(false); 
	return false; 
}
