// ----------------------------------------------------------------
// From "Algorithms and Game Programming" in C++ by Alessandro Bria
// Copyright (C) 2024 Alessandro Bria (a.bria@unicas.it). 
// All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "LevelLoader.h"
#include "SpriteFactory.h"
#include "RenderableObject.h"
#include "StaticObject.h"
#include "ClimbableWalls.h"
#include "PlatformerGameScene.h"
#include "Mario.h"
#include "Lift.h"
#include "Trigger.h"
#include "RangedKappa.h"
#include "Bat.h"
#include "GreenKappa.h"
#include "Skelouton.h"
#include "Bridge.h"
#include "Emerald.h"
#include "Crystal.h"
#include "View.h"
#include "NinjaLift.h"
#include "Spikes.h"
#include "InstaDeathBlock.h"

#include "json.hpp"
#include "mathUtils.h"
#include "Candlestick.h"
#include <iostream>
#include <fstream>

using namespace agp;

LevelLoader::LevelLoader()
{
	LLReset();
}

void LevelLoader::loadJson(
	PlatformerGameScene* world,
	const std::string& jsonPath,
	Mario* mario)
{
	std::ifstream f(jsonPath);
	if (!f.is_open())
		return;

	nlohmann::json jRoot = nlohmann::json::parse(f);
	std::vector <std::string> _categories = jRoot["categories"].get<std::vector<std::string>>();
	std::vector<nlohmann::json> jsonObjects = jRoot["objects"].get<std::vector<nlohmann::json>>();

	for (auto& jObj : jsonObjects)
	{
		int category = jObj["category"];
		std::string name = jObj["name"];

		if (jObj.contains("rect"))
		{
			RectF rect;
			rect.pos.x = jObj["rect"]["x"];
			rect.pos.y = jObj["rect"]["y"];
			rect.size.x = jObj["rect"]["width"];
			rect.size.y = jObj["rect"]["height"];
			rect.yUp = jObj["rect"]["yUp"];

			if (_categories[category] == "Pavements")
				new StaticObject(world, rect, nullptr, false, 1);
			else if (_categories[category] == "Climbable Walls")
				new ClimbableWalls(world, rect, nullptr, 1);
			else if (_categories[category] == "Spikes")
				new Spikes(world, rect, nullptr, 1);
			else if (_categories[category] == "Bridges")
				new Bridge(world, rect, nullptr, 1);
			else if (_categories[category] == "InstadeathBlock")
				new InstaDeathBlock(world, rect, nullptr, 1);
		}
	}

	f.close();
}

Scene* LevelLoader::load(const std::string& name)
{
	SpriteFactory* spriteLoader = SpriteFactory::instance();

	// Qui si caricano solo ed esclusivamente stanze, forse i lift
	if (name == "overworld")
	{
		PlatformerGameScene* world = new PlatformerGameScene(RectF(0, -12, 224, 15), { 16,16 }, 1 / 100.0f);
		world->setBackgroundColor(Color(92, 148, 252));

		// Room1
		new StaticObject(world, RectF(0, 5, 162, 19), spriteLoader->get("room1"), true, -2);
		new Candlestick(world, RectF(25.6f, 15.5f, 2.5f, 2.5f));
		new Candlestick(world, RectF(54, 8, 2.5f, 2.5f));
		new Candlestick(world, RectF(75, 8.5f, 2.5f, 2.5f));
		new Candlestick(world, RectF(82, 19, 2.5f, 2.5f));
		new Candlestick(world, RectF(103, 13, 2.5f, 2.5f));
		new Candlestick(world, RectF(123, 16, 2.5f, 2.5f));
		new Emerald(world, RectF(23, 17, 1.2f, 1.8f));
		new Emerald(world, RectF(29.5f, 17, 1.2f, 1.8f));
		new Emerald(world, RectF(21, 19, 1.2f, 1.8f));
		new Emerald(world, RectF(31.6f, 19, 1.2f, 1.8f));

		// Room2
		new StaticObject(world, RectF(0, 25, 101, 28), spriteLoader->get("room2"), true, -2);
		new Candlestick(world, RectF(67, 40, 2.5f, 2.5f));
		new Candlestick(world, RectF(78, 40, 2.5f, 2.5f));
		new Candlestick(world, RectF(89, 40, 2.5f, 2.5f));
		new Candlestick(world, RectF(9.5, 40, 2.5f, 2.5f));
		new Candlestick(world, RectF(28.2, 40, 2.5f, 2.5f));
		new Crystal(world, RectF(18, 40.9f, 4, 6.5f));

		// Room3
		new StaticObject(world, RectF(0, 54, 46, 22), spriteLoader->get("room3"), true, -2);
		new Candlestick(world, RectF(37.7f, 61, 2.5f, 2.5f));
		new Candlestick(world, RectF(37.7f, 68, 2.5f, 2.5f));
		new Candlestick(world, RectF(14, 59, 2.5f, 2.5f));
		new Candlestick(world, RectF(14, 68, 2.5f, 2.5f));
		new Candlestick(world, RectF(7, 63.5f, 2.5f, 2.5f));
		new Candlestick(world, RectF(21, 63.5f, 2.5f, 2.5f));

		// Room4
		new StaticObject(world, RectF(54, 54, 42, 21), spriteLoader->get("room4"), true, -2);
		new Candlestick(world, RectF(57, 60, 2.5f, 2.5f));
		new Candlestick(world, RectF(62, 60, 2.5f, 2.5f));
		new Candlestick(world, RectF(86, 66, 2.5f, 2.5f));
		new Candlestick(world, RectF(92, 66, 2.5f, 2.5f));

		// Room5
		new StaticObject(world, RectF(99, 54, 47, 47), spriteLoader->get("room5"), true, -2);

		// Room6
		new StaticObject(world, RectF(149, 54, 64, 18), spriteLoader->get("room6"), true, -2);
		new Candlestick(world, RectF(162, 60, 2.5f, 2.5f));
		new Candlestick(world, RectF(174, 56.5F, 2.5f, 2.5f));
		new Candlestick(world, RectF(182, 56.5F, 2.5f, 2.5f));
		new Candlestick(world, RectF(195, 60, 2.5f, 2.5f));
		new Candlestick(world, RectF(171, 66, 2.5f, 2.5f));
		new Candlestick(world, RectF(187, 66, 2.5f, 2.5f));
		new Emerald(world, RectF(207.3f, 69, 1.2f, 1.8f));

		// Room9
		new StaticObject(world, RectF(0, 103, 142, 24), spriteLoader->get("room9"), true, -2);
		new Candlestick(world, RectF(99.5f, 107, 2.5f, 2.5f));
		new Emerald(world, RectF(32.5f, 104, 1.2f, 1.8f));
		new Emerald(world, RectF(32.5f, 107, 1.2f, 1.8f));
		new Emerald(world, RectF(111, 115, 1.2f, 1.8f));
		new Emerald(world, RectF(111, 118, 1.2f, 1.8f));
		new Emerald(world, RectF(111, 121, 1.2f, 1.8f));
		new Emerald(world, RectF(133.8f, 111, 1.2f, 1.8f));
		new Emerald(world, RectF(133.8f, 114, 1.2f, 1.8f));
		new Emerald(world, RectF(133.8f, 117, 1.2f, 1.8f));
		new Emerald(world, RectF(60, 106, 1.2f, 1.8f));
		new Emerald(world, RectF(62, 108, 1.2f, 1.8f));
		new Emerald(world, RectF(56, 106, 1.2f, 1.8f));
		new Emerald(world, RectF(58, 108, 1.2f, 1.8f));
		new Emerald(world, RectF(52, 106, 1.2f, 1.8f));
		new Emerald(world, RectF(54, 108, 1.2f, 1.8f));
		new Emerald(world, RectF(79.5f, 108, 1.2f, 1.8f));
		new Emerald(world, RectF(81.5f, 106, 1.2f, 1.8f));
		new Emerald(world, RectF(83.5f, 108, 1.2f, 1.8f));
		new Emerald(world, RectF(85.5f, 106, 1.2f, 1.8f));
		new Emerald(world, RectF(87.5f, 108, 1.2f, 1.8f));
		new Emerald(world, RectF(89.5f, 106, 1.2f, 1.8f));

		// Room10
		new StaticObject(world, RectF(0, 129, 43, 22), spriteLoader->get("room10"), true, -2);
		new Candlestick(world, RectF(16, 142, 2.5f, 2.5f));
		new Candlestick(world, RectF(24, 142, 2.5f, 2.5f));
		new Candlestick(world, RectF(6.2f, 142, 2.5f, 2.5f));
		new Candlestick(world, RectF(32.5f, 142, 2.5f, 2.5f));

		// Room11
		new StaticObject(world, RectF(46, 129, 41, 21), spriteLoader->get("room11"), true, -2);

		// Room12
		new StaticObject(world, RectF(90, 129, 66, 17), spriteLoader->get("room12"), true, -2);
		new Candlestick(world, RectF(106.5f, 136, 2.5f, 2.5f));
		new Candlestick(world, RectF(121, 136, 2.5f, 2.5f));

		// Spawn point finale per Mario
		//Mario* mario = new Mario(world, PointF(0.7f, 6));
		Mario* mario = new Mario(world, PointF(130, 16));
		world->setPlayer(mario);

		// Caricamento collider da file json
		loadJson(world, std::string(SDL_GetBasePath()) + "collider/EditorScene.json", mario);

		// Trigger per lo spawn dei nemici, utilizzeremo anche le variabli marioInRoom per la gestione della camera
		new Trigger(world, RectF(9.5f, 15.5f, 0.1f, 7.5f), mario, [&, world]()
			{
				_atSpawnPoint = false;
				_marioInRoom1 = true;
				fillRoom1(world);
			});
		new Trigger(world, RectF(127, 3.5f, 6, 0.1f), mario, [&, world]()
			{
				_marioInRoom1 = false;
				killRoom();

				fillRoom2(world);
				_marioInRoom2 = true;
			});
		new Trigger(world, RectF(150, 6, 0.1f, 8), mario, [&, world]()
			{
				_room1StopCamera = true;
			});
		new Trigger(world, RectF(153, 25, 7, 0.1f), mario, [&, world]()
			{
				_room1StopCamera = false;
				_marioInRoom1 = false;
				killRoom();

				//fillRoom3(world);
				_marioInRoom3 = true;
			});

		return world;
	}
	else
	{
		std::cerr << "Unrecognized game scene name \"" << name << "\"\n";
		return nullptr;
	}
}

void LevelLoader::fillRoom1(PlatformerGameScene* world)
{
	Skelouton* skl1 = new Skelouton(world, PointF(52, 12));
	Skelouton* skl2 = new Skelouton(world, PointF(75, 12));
	Skelouton* skl3 = new Skelouton(world, PointF(89, 20));
	Skelouton* skl4 = new Skelouton(world, PointF(124, 21));

	RangedKappa* rkappa1 = new RangedKappa(world, PointF(90, 10));
	RangedKappa* rkappa2 = new RangedKappa(world, PointF(143, 17));
	RangedKappa* rkappa3 = new RangedKappa(world, PointF(139, 20));

	GreenKappa* gkappa1 = new GreenKappa(world, PointF(104, 16));

	skeloutons = { {1, skl1}, {2, skl2}, {3, skl3}, {4, skl4} };
	rangedKappas = { {1, rkappa1}, {2, rkappa2},  {3, rkappa3} };
	greenKappas = { {1, gkappa1} };

	return;
}

void LevelLoader::fillRoom2(PlatformerGameScene* world)
{
	Bat* bat1 = new Bat(world, PointF(80, 35));

	bats = { {1, bat1} };
}

void LevelLoader::fillRoom3(PlatformerGameScene* world)
{
	Bat* bat1 = new Bat(world, PointF(7, 58));

	bats = { {1, bat1} };
}

void LevelLoader::fillRoom6(PlatformerGameScene* world)
{
	Skelouton* skl1 = new Skelouton(world, PointF(175, 68));
	Skelouton* skl2 = new Skelouton(world, PointF(184, 68));

	Bat* bat1 = new Bat(world, PointF(194, 57));

	GreenKappa* gkappa1 = new GreenKappa(world, PointF(162, 63));

	skeloutons = { {1, skl1}, {2, skl2} };
	bats = { {1, bat1} };
	greenKappas = { {1, gkappa1} };
}

void LevelLoader::fillRoom9(PlatformerGameScene* world)
{
	RangedKappa* rkappa1 = new RangedKappa(world, PointF(47, 109));
	RangedKappa* rkappa2 = new RangedKappa(world, PointF(94, 110));

	rangedKappas = { {1, rkappa1}, {2, rkappa2} };
}

void LevelLoader::fillRoom11(PlatformerGameScene* world)
{
	RangedKappa* rkappa1 = new RangedKappa(world, PointF(48, 138));

	rangedKappas = { {1, rkappa1} };
}

void LevelLoader::fillRoom12(PlatformerGameScene* world)
{
	RangedKappa* rkappa1 = new RangedKappa(world, PointF(98, 138));

	Bat* bat1 = new Bat(world, PointF(109, 131));
	Bat* bat2 = new Bat(world, PointF(119, 133));
	Bat* bat3 = new Bat(world, PointF(130, 135));

	rangedKappas = { {1, rkappa1} };
	bats = { {1, bat1}, {2, bat2}, {3, bat3} };
}

void LevelLoader::killRoom()
{
	for (auto& p : rangedKappas)
		p.second->kill();
	for (auto& p : greenKappas)
		p.second->kill();
	for (auto& p : skeloutons)
		p.second->kill();
	for (auto& p : bats)
		p.second->kill();

	rangedKappas.clear();
	greenKappas.clear();
	skeloutons.clear();
	bats.clear();
}

void LevelLoader::LLReset()
{
	_atSpawnPoint = false; //Da mettere a true a fine del debug
	_marioInRoom1 = true;
	_marioInRoom2 = false;
	_marioInRoom3 = false;
	_marioInRoom4 = false;
	_marioInRoom5 = false;
	_marioInRoom6 = false;
	_marioInRoom9 = false;
	_marioInRoom10 = false;
	_marioInRoom11 = false;
	_marioInRoom12 = false;

	_room1StopCamera = false;
	_prevInRoom1 = false;
	_prevInRoom2 = false;
	_prevInRoom3 = false;
	_prevInRoom4 = false;
	_prevInRoom5 = false;
	_prevInRoom6 = false;
	_prevInRoom9 = false;
	_prevInRoom10 = false;
	_prevInRoom11 = false;
	_prevInRoom12 = false;
}