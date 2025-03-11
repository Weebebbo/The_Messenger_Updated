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
#include "HammerBrother.h"
#include "Lift.h"
#include "Trigger.h"
#include "RangedKappa.h"
#include "Bat.h"
#include "GreenKappa.h"
#include "Skelouton.h"
#include "StaticLift.h"
#include "Emerald.h"
#include "Crystal.h"
#include "View.h"
#include "json.hpp"
#include "mathUtils.h"
#include <iostream>
#include <fstream>

using namespace agp;

LevelLoader::LevelLoader()
{
	// e.g. load level data from disk
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
				new StaticObject(world, rect, nullptr, 1);
			else if (_categories[category] == "Climbable Walls")
				new ClimbableWalls(world, rect, nullptr, 1);
		}
	}

	f.close();
}

Scene* LevelLoader::load(const std::string& name)
{
	SpriteFactory* spriteLoader = SpriteFactory::instance();

	if (name == "overworld")
	{
		PlatformerGameScene* world = new PlatformerGameScene(RectF(0, -12, 224, 15), { 16,16 }, 1 / 100.0f);
		world->setBackgroundColor(Color(92, 148, 252));

		// terrain
		new StaticObject(world, RectF(0, -13, 162, 19),  spriteLoader->get("terrain"), -2);
	
		// Enemies 
		//RangedKappa* rKappa1 = new RangedKappa(world, PointF(10, 1));
		//RangedKappa* rKappa2 = new RangedKappa(world, PointF(13, 1));
		//Bat* bat1 = new Bat(world, PointF(10, 0));
		//GreenKappa* gKappa1 = new GreenKappa(world, PointF(10, 1)); 
		//Skelouton* skl1 = new Skelouton(world, PointF(10, 1)); 

		// static lifts
		//StaticLift* prova = new StaticLift(world, RectF(4, 1.8f, 3, 0.5f), spriteLoader->get("platform")); 
		//StaticObject* moneta = new StaticObject(world, RectF(4, 2, 1, 1), spriteLoader->get("money"));
		Crystal* crystal = new Crystal(world, RectF(12, 4, 1, 1), -1);
		StaticLift* prova = new StaticLift(world, RectF(4, 1.8f, 3, 0.5f), spriteLoader->get("platform")); 
		//StaticObject* moneta = new StaticObject(world, RectF(4, 2, 1, 1), spriteLoader->get("money"));
		//Emerald* emerald1 = new Emerald(world, RectF(6, 2, 1, 1));
		//Emerald* emerald2 = new Emerald(world, RectF(8, 2, 1, 1));
		//Emerald* emerald3 = new Emerald(world, RectF(12, 2, 1, 1));

		// mario
		Mario* mario = new Mario(world, PointF(2.5, 0));
		world->setPlayer(mario);

		// Caricamento colider da file json
		loadJson(world, std::string(SDL_GetBasePath()) + "collider/EditorScene.json", mario);

		return world;
	}
	else
	{
		std::cerr << "Unrecognized game scene name \"" << name << "\"\n";
		return nullptr;
	}
}