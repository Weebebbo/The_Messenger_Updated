//
// Created by webubbu on 17/03/25.
//

#include "Candlestick.h"

#include "SpriteFactory.h"

using namespace agp;

Candlestick::Candlestick (Scene* scene, const RectF& rect, int layer) :
    CollidableObject(scene, rect, nullptr, layer)
{
    _compenetrable = true;
    _fit = false;

    _HaveIspawnedMoney = false;
    _didMarioHitMe = false;

    _sprite = SpriteFactory::instance()->get("crystal_off");
}

