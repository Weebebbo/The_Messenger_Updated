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
    bool _HaveIspawnedMoney;
    bool _didMarioHitMe;

public:
    Candlestick(Scene* scene, const RectF& rect, int layer = 0);
    ~Candlestick() {};

    virtual void update(float dt) override {RenderableObject::update(dt);}

    virtual std::string name() override {
        return strprintf("StaticObject[%d]", _id);
    }
};
