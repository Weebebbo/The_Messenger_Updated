#include "Crystal.h"
#include "StaticObject.h"
#include "SpriteFactory.h"
#include "Sword.h"
#include "Mario.h"
#include "AnimatedSprite.h"
#include "Emerald.h"
#include "PlatformerGameScene.h"

using namespace agp;

Crystal::Crystal(Scene* scene, const RectF& rect, int layer) :
	CollidableObject(scene, rect, nullptr, layer)
{
	_compenetrable = true;
	_fit = false; 
	_health = 3;
	_didMarioHitMe = false;
	_inLoop = false;
	_yGravityForce = 0;

	_collider.adjust(0.1f, 0.1f, -0.1f, -0.3f); 

	_sprite = SpriteFactory::instance()->get("crystal");
}

void Crystal::update(float dt)
{
	CollidableObject::update(dt);

	int seed = 5 + rand() % 11;

	if (_health == 0 && _didMarioHitMe && !_inLoop)
	{
		_inLoop = true;
		_sprite = SpriteFactory::instance()->get("crystal_killed");
		schedule("kill_crystal", dynamic_cast<AnimatedSprite*>(_sprite)->duration(), [this, seed]()
			{
				kill();
				for (int i = 0; i < seed; i++)
				{
					PointF pos = _rect.center();
					Emerald* emerald = new Emerald(scene(), RectF(pos.x + 0.8, pos.y + 0.8, 1.0f, 1.0f), 0);
					scene()->newObject(emerald);
					emerald->randomMove();
				}

				_didMarioHitMe = false;
				_inLoop = false;
			});
	}
	else if (_health == 1 && _didMarioHitMe && !_inLoop)
	{
		_inLoop = true;
		_sprite = SpriteFactory::instance()->get("crystal_almost");
		schedule("almost", dynamic_cast<AnimatedSprite*>(_sprite)->duration(), [this]()
			{
				_inLoop = false;
				_didMarioHitMe = false;
			});

	}
	else if (_health == 2 && _didMarioHitMe && !_inLoop)
	{
		_inLoop = true;
		_sprite = SpriteFactory::instance()->get("crystal_meh");
		schedule("meh", dynamic_cast<AnimatedSprite*>(_sprite)->duration(), [this]()
			{
				_inLoop = false;
				_didMarioHitMe = false;
			});
	}
}

bool Crystal::collision(CollidableObject* with, bool begin, Direction fromDir) {

	Sword* sword = dynamic_cast<Sword*>(with);

	if (sword && !_didMarioHitMe) 
	{
		RenderableObject* effect = new RenderableObject(scene(), _rect, SpriteFactory::instance()->get("crystal_effect"), 0);
		effect->setSprite(SpriteFactory::instance()->get("crystal_effect"));
		schedule("effect", dynamic_cast<AnimatedSprite*>(effect->sprite())->duration(), [effect]()
			{
				effect->kill();
			});

		_didMarioHitMe = true;
		_health--;
		return true;
	}
	else
		return false;
}