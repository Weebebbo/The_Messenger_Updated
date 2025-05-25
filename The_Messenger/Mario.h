// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include "DynamicObject.h"
#include <map>
#include <string>

namespace agp
{
	class Mario;
	class Sword;
}

class agp::Mario : public DynamicObject
{
private:

	bool _walking;
	bool _invincible;
	bool _dying;
	bool _dead;
	bool _didMarioHitPotion;
	int _coins;

	int _iterator;

	bool _hitFromLeft;
	bool _hitFromRight;
	bool _hitFromBottom;
	bool _canMarioTakeDamage;
	Uint32 _invincibilityStart;
	bool _damageSkid;
	int _counter;

	bool _standingAttack1;
	bool _standingAttack2;
	bool _runningAttack;
	bool _jumpingAttack;
	bool _crouchAttack;

	bool _canDescend;
	bool _collisionWithLift;
	bool _canCrouch;

	bool _isSwimming;

	double _xLastNonZeroVel;
	Sword* _sword;

	bool _rise;
	bool _ball;
	bool _fall;
	bool _crouch;
	bool _prevCrouch;
	bool _wantsToClimb;
	bool _climbingMovement;
	bool _finishedClimbableWallUpperLimit;
	bool _finishedClimbableWallLowerLimit;
	bool _canMarioJumpAgain;
	bool _iWantToJumpAgain;

	std::map<std::string, Sprite*> _sprites;

public:

	Mario(Scene* scene, const PointF& pos);

	//menu function
	void toggleInvincible();

	bool invincible() { return _invincible; }

	// Getter
	bool get_walking() { return _walking; }
	bool get_wantsToClimb() { return _wantsToClimb; }
	bool get_climbingMovement() { return _climbingMovement; }
	bool get_crouch() { return _crouch; }
	bool get_rise() { return _rise; }
	bool get_ball() { return _ball; }
	bool get_fall() { return _fall; }
	bool get_canDescend() { return _canDescend; }
	bool get_collisionWithLift() { return _collisionWithLift; }
	bool get_finishedClimbingWallUpperLimit() { return _finishedClimbableWallUpperLimit; }
	bool get_finishedClimbingWallLowerLimit() { return _finishedClimbableWallLowerLimit; }
	bool get_canMarioJumpAgain() { return _canMarioJumpAgain; }
	bool get_iWantToJumpAgain() { return _iWantToJumpAgain; }
	Vec2Df get_prevVel() { return _prevVel; }
	bool get_hitFromLeft() { return _hitFromLeft; }
	bool get_hitFromRight() { return _hitFromRight; }
	bool get_hitFromBottom() { return _hitFromBottom; }
	bool get_canMarioTakeDamage() { return _canMarioTakeDamage; }
	bool get_damageSkid() { return _damageSkid; }
	int get_coins() { return _coins; }
	bool get_isSwimming() { return _isSwimming; }
	int get_iterator() { return _iterator; }
	bool get_didMarioHitPotion() { return _didMarioHitPotion; }

	// Setter
	void set_wantsToClimb(bool isClinbing) { _wantsToClimb = isClinbing; }
	void set_climbingMovement(bool climbingMovement) { _climbingMovement = climbingMovement; }
	void set_canDescend(bool canDescend) { _canDescend = canDescend; }
	void set_collisionWithLift(bool collisionWithLift) { _collisionWithLift = collisionWithLift; }
	void set_finishedClimbingWallUpperLimit(bool finished) { _finishedClimbableWallUpperLimit = finished; }
	void set_finishedClimbingWallLowerLimit(bool finished) { _finishedClimbableWallLowerLimit = finished; }
	void set_canMarioJumpAgain(bool canJump) { _canMarioJumpAgain = canJump; }
	void set_iWantToJumpAgain(bool iWantToJump) { _iWantToJumpAgain = iWantToJump; }
	void set_canMarioTakeDamage(bool canMarioTakeDamage) { _canMarioTakeDamage = canMarioTakeDamage; }
	void set_isSwimming(bool is) { _isSwimming = is; }
	void set_rise(bool rise) { _rise = rise; }
	void set_gravity(float g) { _yGravityForce = g; }
	void set_didMarioHitPotion(bool did) { _didMarioHitPotion = did; }

	// extends game logic (+mario logic)
	virtual void update(float dt) override;

	// player actions
	virtual void move(Direction dir) override;
	virtual void jump(bool on = true);
	void crouch(bool on = true);
	void climb_stationary();
	void climbing_movement(float dt, Direction dir);
	void descend() { _canDescend = true; }
	void heal();
	void swimming();

	// scripted actions
	virtual void attack();
	virtual void die();
	virtual void hurt();

	virtual std::string name() override { return strprintf("Mario[%d]", _id); }
	virtual void defaultCollider() override { _collider = { 0.6f, -0.1f, 1.3f, 2.4f }; };
};