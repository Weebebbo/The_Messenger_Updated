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
		
		bool _healthBar[5]; 
		int _iterator;

		bool _hitFromLeft; 
		bool _hitFromRight; 
		bool _hitFromBottom;
		bool _canMarioTakeDamage;
		Uint32 invincibilityStart = 0;
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

		// Roba per le stanze
		bool _marioInRoom1;
		bool _marioInRoom2;
		bool _marioInRoom3;
		bool _marioInRoom4;
		bool _marioInRoom5;
		bool _marioInRoom6;
		bool _marioInRoom9;
		bool _marioInRoom10;
		bool _marioInRoom11;
		bool _marioInRoom12;
		
		std::map<std::string, Sprite*> _sprites;

	public:

		Mario(Scene* scene, const PointF& pos);

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

		// Roba per le stanze
		bool get_marioInRoom1() { return _marioInRoom1; }
		bool get_marioInRoom2() { return _marioInRoom2; }
		bool get_marioInRoom3() { return _marioInRoom3; }
		bool get_marioInRoom4() { return _marioInRoom4; }
		bool get_marioInRoom5() { return _marioInRoom5; }
		bool get_marioInRoom6() { return _marioInRoom6; }
		bool get_marioInRoom9() { return _marioInRoom9; }
		bool get_marioInRoom10() { return _marioInRoom10; }
		bool get_marioInRoom11() { return _marioInRoom11; }
		bool get_marioInRoom12() { return _marioInRoom12; }

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

		// Roba per le stanze
		void set_marioInRoom1(bool isInRoom1) { _marioInRoom1 = isInRoom1; }
		void set_marioInRoom2(bool isInRoom2) { _marioInRoom2 = isInRoom2; }
		void set_marioInRoom3(bool isInRoom3) { _marioInRoom3 = isInRoom3; }
		void set_marioInRoom4(bool isInRoom4) { _marioInRoom4 = isInRoom4; }
		void set_marioInRoom5(bool isInRoom5) { _marioInRoom5 = isInRoom5; }
		void set_marioInRoom6(bool isInRoom6) { _marioInRoom6 = isInRoom6; }
		void set_marioInRoom9(bool isInRoom9) { _marioInRoom9 = isInRoom9; }
		void set_marioInRoom10(bool isInRoom10) { _marioInRoom10 = isInRoom10; }
		void set_marioInRoom11(bool isInRoom11) { _marioInRoom11 = isInRoom11; }
		void set_marioInRoom12(bool isInRoom12) { _marioInRoom12 = isInRoom12; }

		// extends game logic (+mario logic)
		virtual void update(float dt) override;

		// player actions
		virtual void move(Direction dir) override;
		virtual void jump(bool on = true);
		void crouch(bool on = true);
		void climb_stationary();
		void climbing_movement();
		void descend() { _canDescend = true; }

		// scripted actions
		virtual void attack(); 
		virtual void die();
		virtual void hurt();

		virtual std::string name() override { return strprintf("Mario[%d]", _id); }
		virtual void defaultCollider() override { _collider = { 0.6f, -0.1f, 1.3f, 2.4f }; };
};