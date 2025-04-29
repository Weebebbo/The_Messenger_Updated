#include "Potion.h"
#include "Mario.h"
#include "StaticObject.h"

using namespace agp;

Potion::Potion(Scene* scene, const PointF& pos) :
    CollidableObject(scene, RectF(pos.x, pos.y, 2, 2), nullptr)
{

}

void Potion::update(float dt)
{
    CollidableObject::update(dt);
}

bool Potion::collidableWith(CollidableObject* obj)
{
    if (dynamic_cast<Mario*>(obj))
        return true;
    else if (dynamic_cast<StaticObject*>(obj))
        return true;
    else
        return false;
}

bool Potion::collision(CollidableObject* with, bool begin, Direction fromDir)
{
    Mario* mario = dynamic_cast<Mario*>(with);

    if(mario)
    {
        mario->set_didMarioHitPotion(true);
        mario->heal();
        kill();
        return true;
    }
    else
      return false;
}