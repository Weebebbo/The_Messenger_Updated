//
// Created by webubbu on 17/03/25.
//
#include "Candlestick.h"
#include "SpriteFactory.h"
#include "Sword.h"
#include "Emerald.h"
#include "PlatformerGameScene.h"
#include "Potion.h"

using namespace agp;

Candlestick::Candlestick (Scene* scene, const RectF& rect, int layer) :
    CollidableObject(scene, rect, nullptr, layer)
{
    _compenetrable = true;
    _fit = false;

    _haveIspawnedMoney = false;
    _didMarioHitMe = false;
	_wasIhitBefore = false;
    _howManyEmeralds = 0;

    _sprite = SpriteFactory::instance()->get("candlestick_on");

    _collider.adjust(0.1f, 0.1f, -0.1f, -0.1f);
}

void Candlestick::update(float dt)
{
    RenderableObject::update(dt);

    //Genero un numero randomico di gemme per ogni candelabro diverso, compreso tra 1 e 7
    _howManyEmeralds = 1 + (std::rand() % 7);

    //seed per generare le pozioni
    int seed = std::rand() % 8;

    if (_didMarioHitMe && !_wasIhitBefore)
    {
        for (int i = 0; i < _howManyEmeralds; i++)
        {
            PointF pos = this->pos();
            Emerald* emerald = new Emerald(scene(), RectF(pos.x + 0.8, pos.y + 0.8, 1.0f, 1.0f), 0);
            scene()->newObject(emerald);
            emerald->randomMove();
        }

        if(seed % 3 == 0)
        {
            Potion* potion = new Potion(scene(), _rect.center());
            scene()->newObject(potion);
        }

        _didMarioHitMe = false;
        _wasIhitBefore = true;
    }
}


bool Candlestick::collidableWith(CollidableObject* obj)
{
    if (dynamic_cast<Sword*>(obj))
        return true;
}

bool Candlestick::collision(CollidableObject* with, bool begin, Direction fromDir)
{
    Sword* sword = dynamic_cast<Sword*>(with);

    if (sword)
    {
        _didMarioHitMe = true;
		_sprite = SpriteFactory::instance()->get("candlestick_off");
        return true;
    }
    else
        return false;
}