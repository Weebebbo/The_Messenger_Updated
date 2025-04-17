#include "Spikes.h"
#include "Mario.h"

using namespace agp;

Spikes::Spikes (Scene* scene, const RectF& rect, int layer) :
    CollidableObject(scene, rect, nullptr, layer)
{

}

bool Spikes::collidableWith(CollidableObject* obj)
{
    if(dynamic_cast<Mario*>(obj))
      return true;
    else
      return false;
}

bool Spikes::collision(CollidableObject* with, bool begin, Direction fromDir)
{
    Mario* mario = dynamic_cast<Mario*>(with);

    if(mario)
    {
      mario->hurt();
      return true;
    }
    else
      return false;
}