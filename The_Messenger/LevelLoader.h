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

		bool _atSpawnPoint;
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

		// Boleani necessari per il movimento della camera
		bool _room1StopCamera;

		bool _prevInRoom1;
		bool _prevInRoom2;
		bool _prevInRoom3;
		bool _prevInRoom4;
		bool _prevInRoom5;
		bool _prevInRoom6;
		bool _prevInRoom9;
		bool _prevInRoom10;
		bool _prevInRoom11;
		bool _prevInRoom12;

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
		bool get_atSpawnPoint() { return _atSpawnPoint; }
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

		bool get_room1StopCamera() { return _room1StopCamera; }
		bool get_prevInRoom1() { return _prevInRoom1; }
		bool get_prevInRoom2() { return _prevInRoom2; }
		bool get_prevInRoom3() { return _prevInRoom3; }
		bool get_prevInRoom4() { return _prevInRoom4; }
		bool get_prevInRoom5() { return _prevInRoom5; }
		bool get_prevInRoom6() { return _prevInRoom6; }
		bool get_prevInRoom9() { return _prevInRoom9; }
		bool get_prevInRoom10() { return _prevInRoom10; }
		bool get_prevInRoom11() { return _prevInRoom11; }
		bool get_prevInRoom12() { return _prevInRoom12; }

		void set_prevInRoom1(bool b) { _prevInRoom1 = b; }
		void set_prevInRoom2(bool b) { _prevInRoom2 = b; }
		void set_prevInRoom3(bool b) { _prevInRoom3 = b; }
		void set_prevInRoom4(bool b) { _prevInRoom4 = b; }
		void set_prevInRoom5(bool b) { _prevInRoom5 = b; }
		void set_prevInRoom6(bool b) { _prevInRoom6 = b; }
		void set_prevInRoom9(bool b) { _prevInRoom9 = b; }
		void set_prevInRoom10(bool b) { _prevInRoom10 = b; }
		void set_prevInRoom11(bool b) { _prevInRoom11 = b; }
		void set_prevInRoom12(bool b) { _prevInRoom12 = b; }

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
