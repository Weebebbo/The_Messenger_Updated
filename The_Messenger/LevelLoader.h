// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once

#include <string>
#include "PlatformerGameScene.h"
#include "Singleton.h"
#include "Bat.h"
#include "Skelouton.h"
#include "RangedKappa.h"
#include "GreenKappa.h"
#include <map>

namespace agp
{
	class Scene;
	class LevelLoader;
	class PlatformerGameScene;
	class Mario;
}

// LevelLoader (singleton)
// - provides game scene creation methods
class agp::LevelLoader : public Singleton<LevelLoader>
{
	friend class Singleton<LevelLoader>;

	protected:
		// constructor accessible only to Singleton (thanks to friend declaration)
		LevelLoader();

		void loadJson(
			PlatformerGameScene* world,
			const std::string& jsonPath,
			Mario* mario);

		int _marioInRoom;

		// Boleani necessari per il movimento della camera
		bool _room3Movecamera;

		// Map che contengono i nemici
		// I nemici vengono messi dentro una map e poi tolti stanza per stanza
		// Le funzioni che seguono andranno a fare quello
		std::map<int, RangedKappa*> rangedKappas;
		std::map<int, GreenKappa*> greenKappas;
		std::map<int, Skelouton*> skeloutons;
		std::map<int, Bat*> bats;

	public:
		Scene* load(const std::string& name);

		// Getter
		int get_marioInRoom() { return _marioInRoom; }
		bool get_room3MoveCamera() { return _room3Movecamera; }

		// Funzione per la generazione delle stanze
		void fillRoom1(PlatformerGameScene* world);
		void fillRoom2(PlatformerGameScene* world);
		void fillRoom3(PlatformerGameScene* world);
		void fillRoom6(PlatformerGameScene* world);
		void fillRoom9(PlatformerGameScene* world);
		void fillRoom11(PlatformerGameScene* world);
		void fillRoom12(PlatformerGameScene* world);

		// Despawn di tutti i nemici nella stanza
		void killRoom();

		// Reset
		void LLReset();
};
