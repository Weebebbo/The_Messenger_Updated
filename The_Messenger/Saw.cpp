#include "Saw.h"
#include "Mario.h"

using namespace agp;

Saw::Saw(Scene* scene, const RectF& rect, Sprite* sprite, const RectF& path, int vertice, int layer) :
	CollidableObject(scene, rect, sprite, layer)
{
	_fit = false;
	_yGravityForce = 0;

	_vertice = vertice;
	_path = path;
}

void Saw::update(float dt)
{
	CollidableObject::update(dt); 

	if (_vertice == 1)
	{
		setVelY(0);
		setVelX(4);
		if (_rect.right() >= _path.right())
			_vertice = 2;
	}
	else if (_vertice == 2)
	{
		setVelX(0);
		setVelY(-4);
		if (_rect.top() <= _path.top())
			_vertice = 3;
	}
	else if (_vertice == 3)
	{
		setVelY(0);
		setVelX(-4);
		if (_rect.left() <= _path.left())
			_vertice = 4;
	}
	else if (_vertice == 4)
	{
		setVelX(0);
		setVelY(4);
		if (_rect.bottom() >= _path.bottom())
			_vertice = 1;
	}
}

bool Saw::collidableWith(CollidableObject* obj)
{
	return dynamic_cast<Mario*>(obj);
}

bool Saw::collision(CollidableObject* with, bool begin, Direction fromDir)
{
	Mario* mario = dynamic_cast<Mario*>(with);
	
	if (mario)
	{
		mario->hurt();
		return true;
	}
	else
		return false;
}