// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "UIScene.h"
#include "RenderableObject.h"

namespace agp
{
	class HUD;
	class PlatformerGameScene;
}

// HUD
// - implements (as an example) the Super Mario Bros's HUD
class agp::HUD : public UIScene
{
	protected:

		// raw data
		int _score;
		int _coins;
		int _world;
		int _level;
		float _time;
		int _fps;

		// rendering
		RenderableObject* _scoreObj;
		RenderableObject* _flashingCoinObj;
		RenderableObject* _coinsObj;
		RenderableObject* _worldObj;
		RenderableObject* _levelObj;
		RenderableObject* _timeObj;
		RenderableObject* _fpsObj;
		RenderableObject* _healthBar[5]; 

	public:
		
		HUD();
		virtual ~HUD() {};
		
		// getters/setters (to be completed)
		void setFPS(int fps);

		// extends update logic (+time management)
		virtual void update(float timeToSimulate) override;

		// get and set methods
		int get_coins() { return _coins; }
		void set_coins(int coins) { _coins = coins; }

		// add coin method
		void addCoin(); 

		// health bar method
		void healthBar(int iterator);
		
};