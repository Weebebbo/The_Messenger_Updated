#include "FallingBridge.h"
#include "Mario.h"

using namespace agp;

FallingBridge::FallingBridge(Scene* scene, const RectF& rect, Sprite* sprite, int layer) :
    CollidableObject(scene, rect, sprite, layer)
{
    _yGravityForce = 0;
    _hasToFall = false;
    _didMarioHitMe = false;
}

void FallingBridge::update(float dt)
{
    CollidableObject::update(dt);

    if (_hasToFall && !_didMarioHitMe)
    {
        _didMarioHitMe = true;
        _hasToFall = false;
        schedule("falling", 1, [this]()
        {
            _compenetrable = true;
            _didMarioHitMe = false;
            _hasToFall = false;
            setVelY(7);

            schedule("kill", 1, [this]()
            {
                kill();
            });
        });
    }
}

bool FallingBridge::collidableWith(CollidableObject* obj)
{
    return dynamic_cast<Mario*>(obj);
}

bool FallingBridge::collision(CollidableObject* with, bool begin, Direction fromDir)
{
    Mario* mario = dynamic_cast<Mario*>(with);
    if (mario)
    {
        if (fromDir == Direction::UP)
        {
            _hasToFall = true;
            return true;
        }
        else if (fromDir == Direction::DOWN || fromDir == Direction::LEFT || fromDir == Direction::RIGHT)
        {
            _compenetrable = true;

            schedule("go_up", 0.5f, [this]()
            {
                _compenetrable = false;
            });
            return true;
        }
        else
            return false;
    }
}