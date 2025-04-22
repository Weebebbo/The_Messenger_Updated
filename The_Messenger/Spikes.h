//
// Created by webubbu on 17/03/25.
//
#pragma once
#include "CollidableObject.h"

namespace agp
{
    class Spikes;
}

class agp::Spikes : public CollidableObject
{
private:

public:
    Spikes(Scene* scene, const RectF& rect, Sprite* sprite, int layer = 0);
    ~Spikes() {};

    virtual void update(float dt) override {RenderableObject::update(dt);}

    virtual std::string name() override {
        return strprintf("StaticObject[%d]", _id);
    }

    virtual bool collidableWith(CollidableObject* obj) override;
    virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
};
