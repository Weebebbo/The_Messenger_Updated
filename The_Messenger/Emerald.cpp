#include "Emerald.h"
#include "StaticObject.h"
#include "SpriteFactory.h"
#include "PlatformerGame.h"
#include "HUD.h"
#include "Audio.h"

using namespace agp;

Emerald::Emerald(Scene* scene, const RectF& rect, int layer) :
	CollidableObject(scene, rect, nullptr, layer)
{
	_compenetrable = true;
	_fit = false;

	_yGravityForce = 0;
	
	_collider.adjust(0.1f, 0.1f, -0.1f, -0.1f);
	_sprite = SpriteFactory::instance()->get("emerald");
}

void Emerald::update(float dt)
{
	CollidableObject::update(dt);
}

void Emerald::randomMove()
{
	int seed = std::rand() % 10;
	if (seed > 5)
	{
		setVelX(20 - (std::rand() % 20));
		setVelY(4 - (std::rand() % 4));
	}
	else
	{
		setVelX((std::rand() % 20) - 20);
		setVelY((std::rand() % 4) - 4);
	}

	schedule("emerald stop", 0.3, [this]()
		{
			setVelX(0);
			setVelY(0);
		});
}

bool Emerald::collidableWith(CollidableObject* obj)
{
	if (dynamic_cast<Mario*>(obj))
		return true;
}

bool Emerald::collision(CollidableObject* with, bool begin, Direction fromDir) { 

	if (dynamic_cast<Mario*>(with)) {
		dynamic_cast<PlatformerGame*>(Game::instance())->hud()->addCoin();
		Audio::instance()->playSound("Emerald");
		this->kill();
		return true;
	}
	else
		return false;
}