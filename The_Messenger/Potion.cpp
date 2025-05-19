#include "Potion.h"
#include "Mario.h"
#include "StaticObject.h"
#include "PlatformerGame.h"
#include "HUD.h"
#include "SpriteFactory.h"
#include "AnimatedSprite.h"
#include "Bridge.h"

using namespace agp;

Potion::Potion(Scene* scene, const PointF& pos) :
    CollidableObject(scene, RectF(pos.x, pos.y, 1.4f, 1.4f), nullptr)
{
    _sprite = SpriteFactory::instance()->get("potion");

    _collider.adjust(0.2f, 0, -0.2f, 0);
    _compenetrable = true;
    _yGravityForce = 40;
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
    else if (dynamic_cast<Bridge*>(obj))
        return true;
    else
        return false;
}

bool Potion::collision(CollidableObject* with, bool begin, Direction fromDir)
{
    Mario* mario = dynamic_cast<Mario*>(with);

    if(mario && !mario->get_didMarioHitPotion() && mario->get_iterator() != 4)
    {
        mario->set_didMarioHitPotion(true);
        int _iterator = mario->get_iterator();
        mario->heal();
        dynamic_cast<PlatformerGame*>(Game::instance())->hud()->healthBarUp(_iterator, mario);
        
        RenderableObject* effect = new RenderableObject(_scene, _rect, SpriteFactory::instance()->get("potion_effect"));
        schedule("kill", dynamic_cast<AnimatedSprite*>(effect->sprite())->duration(), [this, effect]()
            {
                kill();
                effect->kill();
            });
        return true;
    }
    else
      return false;
}