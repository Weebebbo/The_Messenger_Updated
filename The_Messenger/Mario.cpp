// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Mario.h"
#include "SpriteFactory.h"
#include "Audio.h"
#include "AnimatedSprite.h"
#include "ClimbableWalls.h"
#include "PlatformerGame.h"
#include "PlatformerGameScene.h"
#include "Sword.h"
#include "Scene.h"
#include "Enemy.h"
#include "Fireball.h"

using namespace agp;

const Uint32 INVINCIBILITY_DURATION = 3000;
const Uint32 DAMAGE_SKID_DURATION = 500;

//RectF(pos.x + 1 / 16.0f, pos.y - 2, 2, 2.69)
Mario::Mario(Scene* scene, const PointF& pos)
	: DynamicObject(scene, RectF(pos.x + 1.0f, pos.y - 2.0f, 2.40f, 2.69f), nullptr)
{	
	defaultCollider();
	
	_fit = false;
	_walking = false;
	_dying = false;
	_dead = false;
	_invincible = false;
	
	_hitFromLeft = false; 
	_hitFromRight = false;
	_hitFromBottom = false;
	_canMarioTakeDamage = true;
	_damageSkid = false;
	_counter = 0;

	// Attacco
	_crouchAttack = false;
	_standingAttack1 = false;
	_standingAttack2 = false; 
	_runningAttack = false;
	_jumpingAttack = false;
	_sword = nullptr; 
	
	//Scalata
	_climbingMovement = false;
	_wantsToClimb = false;
	_finishedClimbableWallUpperLimit = false;
	_finishedClimbableWallLowerLimit = false;

	//Discesa
	_canDescend = false; 
	_collisionWithLift = false;
	_canCrouch = true;

	//stati del salto 
	_rise = false;
	_ball = false; 
	_fall = false; 
	_canMarioJumpAgain = false;
	_iWantToJumpAgain = false; // per il doppio salto

	_crouch = false; 
	_prevCrouch = false;

	_xLastNonZeroVel = 0; 
	
	//rimozione di skid e attrito, aggiunta partenza senza transitorio
	_xSkiddingForce = 1000;
	_xFrictionForce = 50;
	_xMoveForce = 60;

	_marioInRoom1 = false;
	_marioInRoom2 = false;
	_marioInRoom3 = false;
	_marioInRoom4 = false;
	_marioInRoom5 = false;
	_marioInRoom6 = false;
	_marioInRoom9 = false;
	_marioInRoom10 = false;
	_marioInRoom11 = false;
	_marioInRoom12 = false;

	// ANIMAZIONI
	_sprites["stand"] = SpriteFactory::instance()->get("ninja_stand");
	_sprites["walk"] = SpriteFactory::instance()->get("ninja_walk");
	_sprites["die"] = SpriteFactory::instance()->get("mario_die");

	_sprites["rise"] = SpriteFactory::instance()->get("jump_rise");
	_sprites["ball"] = SpriteFactory::instance()->get("jump_ball");
	_sprites["fall"] = SpriteFactory::instance()->get("jump_fall");
	_sprites["crouch"] = SpriteFactory::instance()->get("ninja_crouch");
	_sprites["stationary_climb"] = SpriteFactory::instance()->get("ninja_stationaryClimb");
	_sprites["climbMovement"] = SpriteFactory::instance()->get("ninja_climbMovement");

	//Animazioni degli attacchi
	_sprites["running_attack"] = SpriteFactory::instance()->get("running_attack");
	_sprites["jump_attack"] = SpriteFactory::instance()->get("jump_attack");
	_sprites["standing_attack1"] = SpriteFactory::instance()->get("standing_attack1");
	_sprites["standing_attack2"] = SpriteFactory::instance()->get("standing_attack2");
	_sprites["crouch_attack"] = SpriteFactory::instance()->get("crouch_attack");

	//Animazione danno
	_sprites["damage"] = SpriteFactory::instance()->get("ninja_take_damage");

	// Sprite predefinita
	_sprite = _sprites["stand"];

	_iterator = 4;
	for (int i = 0; i < 5; i++) {
		_healthBar[i] = true;
	}
}

void Mario::update(float dt)
{
	// physics
	DynamicObject::update(dt);

	// state logic
	if ((_rise && grounded()) || (_fall && grounded())) {
		_rise = false;
		_fall = false;
	}  
	if (_vel.x != 0 && !_rise)
		_xLastNonZeroVel = _vel.x;
	_walking = _vel.x != 0;

	// Funzione per la scalata, nell'update mette false a _wantsToClimb
	if (_fall || _rise || _ball)
		climb_stationary();

	if (_fall && _wantsToClimb)
		_wantsToClimb = false;
	
	// Cosi' il coso quando � basso non pu� camminare con il collider basso
	if (_crouch && _walking)
		_crouch = false;

	// animations
	if (_dying)
		_sprite = _sprites["die"];
	if (_hitFromLeft || _hitFromRight || _hitFromBottom)
		_sprite = _sprites["damage"]; 
	else if (_standingAttack1) {
		if (_standingAttack2)
			_sprite = _sprites["standing_attack1"];
		else
			_sprite = _sprites["standing_attack2"];
	}
	else if (_runningAttack)
		_sprite = _sprites["running_attack"];
	else if (_jumpingAttack)
		_sprite = _sprites["jump_attack"];
	else if (_crouchAttack)
		_sprite = _sprites["crouch_attack"];
	else if (_wantsToClimb)
		_sprite = _sprites["stationary_climb"];
	else if (_climbingMovement)
		_sprite = _sprites["climbMovement"];
	else if (_rise)
		_sprite = _sprites["rise"];
	else if (_ball)
		_sprite = _sprites["ball"];
	else if (_fall)
		_sprite = _sprites["fall"];
	else if (_walking)
		_sprite = _sprites["walk"];
	else if (_crouch)
		_sprite = _sprites["crouch"];
	else
		_sprite = _sprites["stand"];

	// x-mirroring
	if (!_hitFromLeft && !_hitFromRight && !_hitFromBottom) {
		if (_vel.x < 0 || (_vel.x == 0 && _xLastNonZeroVel < 0))
		{
			_flip = SDL_FLIP_HORIZONTAL;
			if (!_crouch)
				_collider = { 0.35f, -0.1f, 1.3f, 2.4f };
		}
		else
		{
			_flip = SDL_FLIP_NONE;
			if (!_crouch)
				defaultCollider();
		}
	}
	else {
		if (_hitFromLeft) {
			_flip = SDL_FLIP_HORIZONTAL;
		}
		else if (_hitFromRight) {
			_flip = SDL_FLIP_NONE;
		}
		else if (_hitFromBottom && vel().x < 0) {
			_flip = SDL_FLIP_NONE;
		}
		else if (_hitFromBottom && vel().x > 0) {
			_flip = SDL_FLIP_HORIZONTAL;
		}
	}

	if (!_canMarioTakeDamage && (SDL_GetTicks() - invincibilityStart > INVINCIBILITY_DURATION)) {
		_canMarioTakeDamage = true;  // mario puo tornare a prenderlo in culo 
	} 
	else if (!_canMarioTakeDamage && (SDL_GetTicks() - invincibilityStart < INVINCIBILITY_DURATION))
	{
		//implementazione del blinking (quando lo prende in culo mario lampeggia)
		_counter++;

		if (_counter == 40)
			_counter = 0;
		else if (_counter > 20)
			_sprite = nullptr;
	}

	if (_damageSkid && (SDL_GetTicks() - invincibilityStart > DAMAGE_SKID_DURATION)) {
		_damageSkid = false;  // serve per non far attaccare mario mentre scivola
	}
}

void Mario::move(Direction dir)
{
	if (_dying || _dead)
		return;

	DynamicObject::move(dir);
}

void Mario::jump(bool on)
{
	if (_dying || _dead)
		return;

	if (_wantsToClimb || _climbingMovement)
		climb_stationary();

	if (on && !midair() && !_wantsToClimb  && !_climbingMovement || _iWantToJumpAgain)
	{
		// Mario ha bisogno di un impulso maggiore se stava già in aria prima
		// Condizione fatta in casa per far funzionare il doppio salto
		if(_canMarioJumpAgain)
			velAdd(Vec2Df(0, -(2*_yJumpImpulse)));
		else
			velAdd(Vec2Df(0, -_yJumpImpulse));

		if (std::abs(_vel.x) < 9)
			_yGravityForce = 25;
		else
			_yGravityForce = 21;

		_rise = true;
		_canMarioJumpAgain = false;

		schedule("jump_to_ball", 0.2f, [this]()
			{
				_rise = false;
				_ball = true;

				schedule("ball_off", 0.3f, [this]()
					{
						_ball = false;
					});
				_fall = true;
			});

		Audio::instance()->playSound("jump-small");
	}
	else if (!on && midair() && !_dying && !_wantsToClimb)
	{
		_yGravityForce = 90;

		if (vel().y > 0) {
			_ball = false;
			_fall = true;
		}
	}
}

void Mario::climb_stationary()
{
	if (_dying || _dead)
		return;

	if (_wantsToClimb && !_walking)
	{
		_fall = false;
		_ball = false;
		_rise = false;

		_vel = { 0, 0 };
		_yGravityForce = 0;
	}
	else if (_walking && _wantsToClimb)
	{
		_wantsToClimb = false;
		_yGravityForce = 90;
	}
}

void Mario::climbing_movement()
{
	if (_wantsToClimb)
	{
		_wantsToClimb = false;
		_climbingMovement = true;
	}
}

void Mario::crouch(bool on) {
	if (_dying || _dead)
		return;
	
	if (on && !_walking && !midair() && !_wantsToClimb && !_climbingMovement)
	{
		_crouch = true;
		if (_xLastNonZeroVel > 0)
			_collider = { 0.8f, 1.0f, 1.4f, 1.3f };
		else if (_xLastNonZeroVel < 0)
			_collider = { 0.35f, 1.0f, 1.3f, 1.3f };
		_prevCrouch = true;
	}
	else if(_prevCrouch && !on)
	{
		_crouch = false; 
		_prevCrouch = false;
		defaultCollider();
	}
}

void Mario::attack()
{
	if (_dying || _dead)
		return;

	Audio::instance()->playSound("sword");

	_sword = new Sword(this);

	//Scelta dell'animazione per l'attacco
	if (_crouch)
	{
		_crouchAttack = true;
	}
	else if (_walking && !midair())
		_runningAttack = true;
	else if (midair())
		_jumpingAttack = true;
	else {
		_standingAttack1 = true;
		if (_standingAttack2)
			_standingAttack2 = false;
		else
			_standingAttack2 = true; 
	}

	schedule("attacking_off", 0.33f, [this]()
	{
		//Disattivazione dell'attacco
		_runningAttack = false;
		_jumpingAttack = false;
		_crouchAttack = false;
		_standingAttack1 = false;
		});

	_scene->killObject(_sword);
	_sword = nullptr;
}

void Mario::die()
{
	if (_dying)
		return;

	_dying = true;
	_collidable = false;
	_yGravityForce = 0;
	_vel = { 0,0 };   
	_xDir = Direction::NONE;
	Audio::instance()->haltMusic();
	Audio::instance()->playSound("death");
	dynamic_cast<PlatformerGame*>(Game::instance())->freeze(true);

	schedule("dying", 0.5f, [this]()
		{
			_yGravityForce = 25;
			velAdd(Vec2Df(0, -_yJumpImpulse));
			schedule("die", 3, [this]()
				{
					_dead = true;
					dynamic_cast<PlatformerGame*>(Game::instance())->gameover();
				});
		});
}

void Mario::hurt()
{
	if (!_invincible && _canMarioTakeDamage) {
		
		_healthBar[_iterator] = false; //le vite del bro sono gestite tramite un vettore di booleani
		_iterator--; 

		_canMarioTakeDamage = false;
		_damageSkid = true;
		invincibilityStart = SDL_GetTicks();

		if (_facingDir == Direction::RIGHT) {
			_hitFromRight = true;

			if (midair()) {
				velAdd(Vec2Df(0, -3000));
			}

			_xFrictionForce = 10;
			velAdd(Vec2Df(-3000, 0));
			schedule("right_off", 0.5f, [this] {
				_hitFromRight = false;
				_xFrictionForce = 50;
				}, 0);
		}
		else if (_facingDir == Direction::LEFT) {
			_hitFromLeft = true;

			if (midair()) {
				velAdd(Vec2Df(0, -3000));
			}

			_xFrictionForce = 10;
			velAdd(Vec2Df(3000, 0));
			schedule("left_off", 0.5f, [this] {
				_hitFromLeft = false;
				_xFrictionForce = 50;
				}, 0);
		}

		if (_iterator < 0)
			die();
	}
}
