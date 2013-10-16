#ifndef ANIMATIONS
#define ANIMATIONS

#include "Utility.h"

using namespace std;
using namespace sf;

enum AnimType { FINITE, INFINITE };

class AnimFrame
{
private:
	Sprite t;
	long endTime;
public:
	AnimFrame(Sprite t, long endTime)
	{
		this->t = t;
		this->endTime = endTime;
	}

	Sprite getSprite() const 
	{
		return t;
	}

	long getEndTime() const 
	{
		return endTime;
	}

	void setPos( float x, float y )
	{
		t.setPosition(x,y);
	}
};


class Animation
{
protected:
	vector<AnimFrame> frames;
	unsigned int currentFrame;
	long currAnimTime;
	AnimType atype;
	bool isAnimFin;
	float centerX, centerY;

	AnimFrame getFrame(int i) const
	{
		return frames[i];
	}

public:

	Animation()
	{
		currAnimTime = 0;
		currentFrame = 0;

		this->atype = AnimType::INFINITE;
		this->isAnimFin = false;
	}

	Animation(float centerX, float centerY, vector<AnimFrame> animframes)
	{
		currAnimTime = 0;
		currentFrame = 0;

		this->atype = AnimType::FINITE;
		this->isAnimFin = false;
		this->centerX = centerX;
		this->centerY = centerY;
		this->frames = animframes;

		for_each( frames.begin(), frames.end(), [&](AnimFrame& a) { a.setPos(centerX, centerY); } );
	}

	Sprite getSprite() const 
	{
		return getFrame(currentFrame).getSprite();
	}

	vector<AnimFrame> getVectorFrames() const
	{
		return frames;
	}

	bool getIsAnimFin() const
	{
		return isAnimFin;
	}

	void reactivateAnim()
	{
		if( FINITE == atype )
			isAnimFin = false;
	}

	// should not be used
	void addFrame(Sprite t, long duration)
	{
		frames.push_back(AnimFrame(t, duration));
	}

	virtual void update(long elapsedTime)
	{

		if (frames.size() > 1) 
		{
			currAnimTime += elapsedTime;

			if( currAnimTime > getFrame(currentFrame).getEndTime() )
			{
				currAnimTime = 0;
				if( currentFrame < frames.size() - 1 )
					currentFrame++;
				else 
				{
					currentFrame = 0;
					isAnimFin = atype == FINITE ? true : false;
				}
			}
		}

		else 
		{
			currentFrame = 0;
		}
	}

};

#endif