// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Sword.h"
#include "Mario.h"
#include "SpriteFactory.h"
#include "Scene.h"
#include "AnimatedSprite.h"
#include "Enemy.h"
#include "Crystal.h"

using namespace agp;

Sword::Sword(Mario* mario)
	: DynamicObject(mario->scene(), RectF(mario->pos().x, mario->pos().y, 5, 3), nullptr, mario->layer() - 1)
{
	_link = mario;
	_facingDir = _link->facingDir();
	_yGravityForce = 0;
	_CCD = false;

	// Inizializzazione parametri del collider della spada
	_collider = { 1, 0.8, 3, 2 };
}

void Sword::update(float dt)
{
	_facingDir = _link->facingDir();

	// correct position based on Link
	if (_facingDir == Direction::RIGHT)
	{
		setPos(_link->pos() + PointF{  0, -7 / 16.0f });
	}
	else if (_facingDir == Direction::LEFT)
		setPos(_link->pos() + PointF{ -32 / 16.0f, -7 / 16.0f });

	DynamicObject::update(dt);
}

bool Sword::collidableWith(CollidableObject* obj)
{
	Enemy* enemy = dynamic_cast<Enemy*>(obj);
	if (enemy != nullptr)
		return dynamic_cast<Enemy*>(obj);

	Crystal* crystal = dynamic_cast<Crystal*>(obj);
	if (crystal != nullptr)
		return dynamic_cast<Crystal*>(obj);
}

bool Sword::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Enemy* enemy = dynamic_cast<Enemy*>(with);
	if (enemy)
		enemy->smash();
	

	return true;
}