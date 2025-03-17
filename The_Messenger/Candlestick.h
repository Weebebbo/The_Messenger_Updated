//
// Created by webubbu on 17/03/25.
//
#pragma once
#include "CollidableObject.h"

namespace agp
{
    class Candlestick;
}

class agp::Candlestick : public CollidableObject
{
private:


public:
    Candlestick(Scene* scene, const RectF& rect, Sprite* sprite, int layer = 0);

};
