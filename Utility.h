#ifndef UTILITY
#define UTILITY

#include <SFML/Graphics.hpp>
#include <math.h>

namespace UtilMath
{
	float radianForm(float degree)
	{
		return ( degree * 3.1415926545f / 180.0f );
	}
}

class SpriteImpl
{
public:
	SpriteImpl(string filename, float xOrigin, float yOrigin)
	{
		Texture* t = new Texture(); // needs to deleted
		t->loadFromFile(filename);

		Sprite* s = new Sprite(*t);

		s->setOrigin(xOrigin, yOrigin);
	}
	~SpriteImpl()
	{
		delete t;
		delete s;
	}

	Sprite* getSprite() const
	{
		return s;
	}

private:
	Texture* t;
	Sprite* s;
};


#endif