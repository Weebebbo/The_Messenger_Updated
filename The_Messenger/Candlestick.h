//
// Created by webubbu on 17/03/25.
//

#ifndef CANDLESTICK_H
#define CANDLESTICK_H
#pragma once
#include "CollidableObject.h"

namespace agp
{
    class Candlestick;
}

class agp::Candlestick : public CollidableObject
{
private:
    Candlestick(Scene* scene, const RectF& rect, Sprite* sprite, int layer = 0);
    virtual ~Candlestick() {}

public:
    // extends game logic (-physics, -collisions)
    virtual void update(float dt) override {RenderableObject::update(dt);}

    virtual std::string name() override {
        return strprintf("StaticObject[%d]", _id);
    }

    virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
};


#endif //CANDLESTICK_H
