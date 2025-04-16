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
#include "Candlestick.h"
#include "Enemy.h"
#include "Crystal.h"
#include "PlatformerGameScene.h"

using namespace agp;

Sword::Sword(Mario* mario)
	: DynamicObject(mario->scene(), RectF(mario->pos().x, mario->pos().y, 2.0f, 2.0f), nullptr, mario->layer() - 1)
{
	_link = mario;
	_facingDir = _link->facingDir();
	_yGravityForce = 0;
	_CCD = false;

	// Inizializzazione parametri del collider della spada
	_collider = { 1.5f, 0.8f, 2.5f, 1.5f };
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
		setPos(_link->pos() + PointF{ -50 / 16.0f, -7 / 16.0f });

	DynamicObject::update(dt);
}

bool Sword::collidableWith(CollidableObject* obj)
{
	if (dynamic_cast<Enemy*>(obj))
		return true;
	else if (dynamic_cast<Crystal*>(obj))
		return true;
	else if (dynamic_cast<Candlestick*>(obj))
		return true;
}

bool Sword::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Enemy* enemy = dynamic_cast<Enemy*>(with);
	Mario* mario = dynamic_cast<Mario*>(dynamic_cast<PlatformerGameScene*>(_scene)->player());
	
	if (enemy)
		enemy->smash();
	
	if (!mario->get_canMarioJumpAgain() && (enemy || dynamic_cast<Candlestick*>(with) || dynamic_cast<Crystal*>(with)))
		mario->set_canMarioJumpAgain(true);

	return true;
}