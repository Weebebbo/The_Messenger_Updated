#pragma once
#include "CollidableObject.h"

namespace agp
{
    class FallingBridge;
}

// StaticObject class.
// - provides base class for all objects that do not generally update physics
//   nor detect/resolve collisions
class agp::FallingBridge : public CollidableObject
{

protected:

    bool _hasToFall;
    bool _didMarioHitMe;

public:

    FallingBridge(Scene* scene, const RectF& rect, int layer = 0);
    virtual ~FallingBridge() {}

    // extends game logic (-physics, -collisions)
    virtual void update(float dt) override;

    virtual std::string name() override {
        return strprintf("StaticLift[%d]", _id);
    }

    //methods for collision
    bool collidableWith(CollidableObject* obj) override;
    virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
};