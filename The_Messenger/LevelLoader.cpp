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
#include "Trigger.h"
#include "RangedKappa.h"
#include "Bat.h"
#include "GreenKappa.h"
#include "Skelouton.h"
#include "Bridge.h"
#include "Emerald.h"
#include "Crystal.h"
#include "View.h"
#include "Spikes.h"
#include "InstaDeathBlock.h"
#include "Water.h"
#include "Saw.h"
#include "FallingBridge.h"
#include "FilledSprite.h"
#include "Potion.h"

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
			else if (_categories[category] == "Water")
				new Water(world, rect, nullptr, 1);
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

		//new RangedKappa(world, PointF(15, 20), true);
		//new Bat(world, PointF(20, 10));
		//new GreenKappa(world, PointF(5, 20)); 
		//new Skelouton(world, PointF(8, 18)); 
		//new StaticObject(world, RectF(8, 19, 1, 1), nullptr); 

		world->setBackgroundColor(Color(0, 0, 0));
	
		// Room1
		new StaticObject(world, RectF(0, 28, 162, 19), spriteLoader->get("room1"), true, -2);
		new Candlestick(world, RectF(25.6f, 38.5f, 2.5f, 2.5f));
		new Emerald(world, RectF(23, 40.5f, 1.2f, 1.8f));
		new Emerald(world, RectF(29.5f, 40.5f, 1.2f, 1.8f));
		new Emerald(world, RectF(21, 42.5f, 1.2f, 1.8f));
		new Emerald(world, RectF(31.6f, 42.5f, 1.2f, 1.8f));
		new Candlestick(world, RectF(54, 32, 2.5f, 2.5f));
		new Candlestick(world, RectF(75.5f, 32, 2.5f, 2.5f));
		new Candlestick(world, RectF(82, 42, 2.5f, 2.5f));
		new Candlestick(world, RectF(103, 36, 2.5f, 2.5f));
		new Candlestick(world, RectF(121.5f, 39, 2.5f, 2.5f));


		// Room2
		new StaticObject(world, RectF(67.3f, 0, 101, 28), spriteLoader->get("room2"), true, -2);
		new Candlestick(world, RectF(136, 14, 2.5f, 2.5f));
		new Candlestick(world, RectF(156, 14, 2.5f, 2.5f));
		new Candlestick(world, RectF(146, 14, 2.5f, 2.5f));
		new Candlestick(world, RectF(95.5f, 14, 2.5f, 2.5f));
		new Candlestick(world, RectF(76.7f, 14, 2.5f, 2.5f));
		new Crystal(world, RectF(85.8f, 15.9f, 4, 6.5f));

		// Room3
		new StaticObject(world, RectF(117.3f, 47, 46, 22), spriteLoader->get("room3"), true, -2);
		new Candlestick(world, RectF(131, 52, 2.5f, 2.5f));
		new Candlestick(world, RectF(131, 62, 2.5f, 2.5f));
		new Candlestick(world, RectF(126, 57, 2.5f, 2.5f));
		new Candlestick(world, RectF(136, 57, 2.5f, 2.5f));
		new Candlestick(world, RectF(155, 51, 2.5f, 2.5f));
		new Candlestick(world, RectF(155, 57, 2.5f, 2.5f));

		// Room4
		new StaticObject(world, RectF(163.2f, 48.01f, 42, 21), spriteLoader->get("room4"), true, -2);
		new Candlestick(world, RectF(166.3f, 54, 2.5f, 2.5f));
		new Candlestick(world, RectF(171.3f, 54, 2.5f, 2.5f));
		new Candlestick(world, RectF(195.5f, 59, 2.5f, 2.5f));
		new Candlestick(world, RectF(200.5f, 59, 2.5f, 2.5f));

		// Room5
		new StaticObject(world, RectF(205, 46.8f, 47, 47), spriteLoader->get("room5"), true, -2);

		// Room6
		new StaticObject(world, RectF(252, 49.325f, 64, 18), spriteLoader->get("room6"), true, -2);
		new Candlestick(world, RectF(262, 58, 2.5f, 2.5f));
		new Candlestick(world, RectF(277, 51.8f, 2.5f, 2.5f));
		new Candlestick(world, RectF(285, 51.8f, 2.5f, 2.5f));
		new Candlestick(world, RectF(273.5f, 61.5f, 2.5f, 2.5f));
		new Candlestick(world, RectF(290.5f, 62, 2.5f, 2.5f));
		new Candlestick(world, RectF(303, 58, 2.5f, 2.5f));
		new Emerald(world, RectF(310.3f, 65, 1.2f, 1.8f));

		// Room9
		new StaticObject(world, RectF(277.8f, 67.2f, 142, 24), spriteLoader->get("room9"), true, -2);
		new Candlestick(world, RectF(377, 70, 2.5f, 2.5f));
		new Emerald(world, RectF(310.3f, 69, 1.2f, 1.8f));
		new Emerald(world, RectF(310.3f, 72, 1.2f, 1.8f));
		new Emerald(world, RectF(388.5f, 80, 1.2f, 1.8f));
		new Emerald(world, RectF(388.5f, 83, 1.2f, 1.8f));
		new Emerald(world, RectF(388.5f, 86, 1.2f, 1.8f));
		new Emerald(world, RectF(411.6f, 82, 1.2f, 1.8f));
		new Emerald(world, RectF(411.6f, 79, 1.2f, 1.8f));
		new Emerald(world, RectF(411.6f, 76, 1.2f, 1.8f));
		new Emerald(world, RectF(330, 70, 1.2f, 1.8f));
		new Emerald(world, RectF(331.5f, 72, 1.2f, 1.8f));
		new Emerald(world, RectF(334, 70, 1.2f, 1.8f));
		new Emerald(world, RectF(335.5f, 72, 1.2f, 1.8f));
		new Emerald(world, RectF(338, 70, 1.2f, 1.8f));
		new Emerald(world, RectF(339.5f, 72, 1.2f, 1.8f));
		new Emerald(world, RectF(357.5f, 72, 1.2f, 1.8f));
		new Emerald(world, RectF(359, 70, 1.2f, 1.8f));
		new Emerald(world, RectF(361.5f, 72, 1.2f, 1.8f));
		new Emerald(world, RectF(363, 70, 1.2f, 1.8f));
		new Emerald(world, RectF(365.5f, 72, 1.2f, 1.8f));
		new Emerald(world, RectF(367, 70, 1.2f, 1.8f));
		new Saw(world, RectF(313, 81.3f, 3.5f, 3.5f), spriteLoader->get("saw"), RectF(313, 81.3f, 14.7f, 8.4f), 4);
		new Saw(world, RectF(324.f, 86.2f, 3.5f, 3.5f), spriteLoader->get("saw"), RectF(313, 81.3f, 14.7f, 8.4f), 2);

		// Room10
		new StaticObject(world, RectF(327.8f, 45.4f, 43, 22), spriteLoader->get("room10"), true, -2);
		new Candlestick(world, RectF(334, 59, 2.5f, 2.5f));
		new Candlestick(world, RectF(343.5f, 59, 2.5f, 2.5f));
		new Candlestick(world, RectF(352.5f, 59, 2.5f, 2.5f));
		new Candlestick(world, RectF(360.4f, 59, 2.5f, 2.5f));

		// Room11
		new StaticObject(world, RectF(377.8f, 46.2f, 41, 21), spriteLoader->get("room11"), true, -2);

		// Room12
		new StaticObject(world, RectF(323.5f, 29.5f, 66, 17), spriteLoader->get("room12"), true, -2);
		new Candlestick(world, RectF(354.5f, 37, 2.5f, 2.5f));
		new Candlestick(world, RectF(340, 37, 2.5f, 2.5f));

		//Player
		Mario* mario = new Mario(world, PointF(0.7f, 27));	
		//Mario* mario = new Mario(world, PointF(310, 77));
		world->setPlayer(mario);

		//World
		loadJson(world, std::string(SDL_GetBasePath()) + "collider/EditorScene.json", mario);
		new Trigger(world, RectF(8, 38, 0.1f, 8), mario, [&, world]()
			{
				_marioInRoom = 1;
				killRoom();
				fillRoom1(world);
			});
		//from roo1 to room2
		new Trigger(world, RectF(127, 26.5f, 5, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 1)
				{
					_marioInRoom = 2;
					killRoom();
					fillRoom2(world);
				}
			});
		//from room2 to room1
		new Trigger(world, RectF(127, 29.5f, 5, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 2)
				{
					_marioInRoom = 1;
					killRoom();
					fillRoom1(world);
				}
			});
		//from room1 to room3
		new Trigger(world, RectF(153.5f, 47.5f, 6, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 1)
				{
					_marioInRoom = 3;
					killRoom();
					fillRoom3(world);
				}
			});
		//in room3
		new Trigger(world, RectF(144, 64, 0.1f, 4), mario, [&, world]()
			{
				_room3Movecamera = true;
			});
		new Trigger(world, RectF(146.5f, 64, 0.1f, 4), mario, [&, world]()
			{
				_room3Movecamera = false;
			});
		//from room3 to room1
		new Trigger(world, RectF(153, 45, 6, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 3)
				{
					_marioInRoom = 1;
					killRoom();
					fillRoom1(world);
				}
			});
		//from room3 to room4
		new Trigger(world, RectF(164, 62, 0.1f, 6.5f), mario, [&, world]()
			{
				if (_marioInRoom == 3)
				{
					_marioInRoom = 4;
					killRoom();
				}
			});
		//from room4 to room3
		new Trigger(world, RectF(162, 62, 0.1f, 6.5f), mario, [&, world]()
			{
				if (_marioInRoom == 4)
				{
					_marioInRoom = 3;
					killRoom();
					fillRoom3(world);
				}
			});
		//from room4 to room5
		new Trigger(world, RectF(206.5f, 48, 0.1f, 6.5f), mario, [&, world]()
			{
				if (_marioInRoom == 4)
				{
					_marioInRoom = 5;
					killRoom();
				}
			});
		//from room5 to room4
		new Trigger(world, RectF(203.5f, 49, 0.1f, 6.5f), mario, [&, world]()
			{
				if (_marioInRoom == 5)
				{
					_marioInRoom = 4;
					killRoom();
				}
			});
		//from room5 to room6
		new Trigger(world, RectF(253.5f, 49, 0.1f, 6.5f), mario, [&, world]()
			{
				if (_marioInRoom == 5)
				{
					_marioInRoom = 6;
					killRoom();
					fillRoom6(world);
				}
			});
		//from room6 to room5
		new Trigger(world, RectF(250.5f, 49, 0.1f, 6.5f), mario, [&, world]()
			{
				if (_marioInRoom == 6)
				{
					_marioInRoom = 5;
					killRoom();
				}
			});
		//from room6 to room9
		new Trigger(world, RectF(307, 69, 7, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 6)
				{
					_marioInRoom = 9;
					killRoom();
					fillRoom9(world);
				}
			});
		//from room9 tom room6
		new Trigger(world, RectF(307, 66, 7, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 9)
				{
					_marioInRoom = 6;
					killRoom();
					fillRoom6(world);
				}
			});
		//from room 9 to room11
		new Trigger(world, RectF(409, 65.7, 7, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 9)
				{
					_marioInRoom = 11;
					killRoom();
					fillRoom11(world);
				}
			});
		//from room11 to room9
		new Trigger(world, RectF(409, 68.7, 7, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 11)
				{
					_marioInRoom = 9;
					killRoom();
					fillRoom9(world);
				}
			});
		//from room9 to room10
		new Trigger(world, RectF(346, 65.8, 7, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 9)
				{
					_marioInRoom = 10;
					killRoom();
				}
			});
		//from room10 to room9
		new Trigger(world, RectF(346, 68.8, 7, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 10)
				{
					_marioInRoom = 9;
					killRoom();
					fillRoom9(world);
				}
			});
		//from room11 to room12
		new Trigger(world, RectF(381, 44.8f, 7, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 11)
				{
					_marioInRoom = 12;
					killRoom();
					fillRoom12(world);
				}
			});
		//from room12 to room11	
		new Trigger(world, RectF(381, 47.8f, 7, 0.1f), mario, [&, world]()
			{
				if (_marioInRoom == 12)
				{
					_marioInRoom = 11;
					killRoom();
					fillRoom11(world);
				}
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
	Skelouton* skl1 = new Skelouton(world, PointF(54, 35));
	Skelouton* skl2 = new Skelouton(world, PointF(75, 35));
	Skelouton* skl3 = new Skelouton(world, PointF(89, 43));
	Skelouton* skl4 = new Skelouton(world, PointF(124, 43));

	RangedKappa* rkappa1 = new RangedKappa(world, PointF(90, 32));
	RangedKappa* rkappa2 = new RangedKappa(world, PointF(143, 39));
	RangedKappa* rkappa3 = new RangedKappa(world, PointF(139, 43));

	GreenKappa* gkappa1 = new GreenKappa(world, PointF(104, 38));

	skeloutons = { {1, skl1}, {2, skl2}, {3, skl3}, {4, skl4} };
	rangedKappas = { {1, rkappa1}, {2, rkappa2},  {3, rkappa3} };
	greenKappas = { {1, gkappa1} };

	return;
}

void LevelLoader::fillRoom2(PlatformerGameScene* world)
{
	Bat* bat1 = new Bat(world, PointF(148, 10));

	bats = { {1, bat1} };
}

void LevelLoader::fillRoom3(PlatformerGameScene* world)
{
	Bat* bat1 = new Bat(world, PointF(124, 51));
	bats = { {1, bat1} };
}

void LevelLoader::fillRoom6(PlatformerGameScene* world)
{
	Skelouton* skl1 = new Skelouton(world, PointF(278, 63));
	Skelouton* skl2 = new Skelouton(world, PointF(287, 63));

	Bat* bat1 = new Bat(world, PointF(297, 52));

	GreenKappa* gkappa1 = new GreenKappa(world, PointF(265, 58));

	skeloutons = { {1, skl1}, {2, skl2} };
	bats = { {1, bat1} };
	greenKappas = { {1, gkappa1} };
}

void LevelLoader::fillRoom9(PlatformerGameScene* world)
{
	RangedKappa* rkappa1 = new RangedKappa(world, PointF(324, 73));
	RangedKappa* rkappa2 = new RangedKappa(world, PointF(371, 74));
	FallingBridge* fb1 = new FallingBridge(world, RectF(331, 75, 3, 0.8f));
	FallingBridge* fb2 = new FallingBridge(world, RectF(334, 75, 3, 0.8f));
	FallingBridge* fb3 = new FallingBridge(world, RectF(337, 75, 3, 0.8f));
	FallingBridge* fb4 = new FallingBridge(world, RectF(340, 75, 3, 0.8f));
	FallingBridge* fb5 = new FallingBridge(world, RectF(343, 75, 3, 0.8f));
	FallingBridge* fb6 = new FallingBridge(world, RectF(346, 75, 3, 0.8f));
	FallingBridge* fb7 = new FallingBridge(world, RectF(349, 75, 3, 0.8f));
	FallingBridge* fb8 = new FallingBridge(world, RectF(352, 75, 3, 0.8f));
	FallingBridge* fb9 = new FallingBridge(world, RectF(355, 75, 3, 0.8f));
	FallingBridge* fb10 = new FallingBridge(world, RectF(358, 75, 3, 0.8f));
	FallingBridge* fb11 = new FallingBridge(world, RectF(361, 75, 3, 0.8f));
	FallingBridge* fb12 = new FallingBridge(world, RectF(364, 75, 3, 0.8f));

	fallinBridges = { {1, fb1}, {2, fb2}, {3, fb3}, {4, fb4}, {5, fb5}, {6, fb6}, {7, fb7},
						{8, fb8}, {9, fb9}, {10, fb10}, {11, fb11}, {12, fb12} };
	rangedKappas = { {1, rkappa1}, {2, rkappa2} };
}

void LevelLoader::fillRoom11(PlatformerGameScene* world)
{
	RangedKappa* rkappa1 = new RangedKappa(world, PointF(380, 55));

	rangedKappas = { {1, rkappa1} };
}

void LevelLoader::fillRoom12(PlatformerGameScene* world)
{
	RangedKappa* rkappa1 = new RangedKappa(world, PointF(332, 38));

	Skelouton* skl1 = new Skelouton(world, PointF(362, 38));

	Bat* bat1 = new Bat(world, PointF(343, 32));
	Bat* bat2 = new Bat(world, PointF(356, 32));
	Bat* bat3 = new Bat(world, PointF(364.5f, 35));

	rangedKappas = { {1, rkappa1} };
	bats = { {1, bat1}, {2, bat2}, {3, bat3} };
	skeloutons = { {1, skl1} };
}

void LevelLoader::killRoom()
{
	for (auto& p : rangedKappas)
		if (!p.second->get_killed())
			p.second->kill();
	for (auto& p : greenKappas)
		if (!p.second->get_killed())
			p.second->kill();
	for (auto& p : skeloutons)
		if (!p.second->get_killed())
			p.second->kill();
	for (auto& p : bats)
		if (!p.second->get_killed())
			p.second->kill();
	for (auto& p : fallinBridges)
		if (!p.second->get_killed())
			p.second->kill();

	rangedKappas.clear();
	greenKappas.clear();
	skeloutons.clear();
	bats.clear();
	fallinBridges.clear();
}

void LevelLoader::LLReset()
{
	killRoom();
	_marioInRoom = 1;

	_room3Movecamera = false;
}