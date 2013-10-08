#ifndef UTILITY
#define UTILITY

#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace sf;

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
		t = new Texture(); // needs to deleted
		t->loadFromFile(filename);

		s = new Sprite(*t);

		s->setOrigin(xOrigin, yOrigin);
	}

	explicit SpriteImpl(const SpriteImpl& spriteImpl)
	{
		t = NULL;
		s = new Sprite(*spriteImpl.getSprite());
	}

	~SpriteImpl()
	{
		if( t != NULL )
		{
			delete t;
			t = NULL;
		}
		if( s != NULL )
		{
			delete s;
			s = NULL;
		}
	}

	void setPosition(float x, float y)
	{
		s->setPosition(x,y);
	}

	void setRotation(float theta)
	{
		s->setRotation(theta);
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