#include "CollidableObject.h"

namespace agp
{
    class Potion;
}

class agp::Potion : public CollidableObject
{
private:

public:

    Potion(Scene* scene, const PointF& pos);
    ~Potion() {};

    virtual void update(float dt) override;

    virtual std::string name() override {
        return strprintf("Crystal[%d]", _id);
    }

    //methods for collision
    bool collidableWith(CollidableObject* obj) override;
    virtual bool collision(CollidableObject* with, bool begin, Direction fromDir) override;
};