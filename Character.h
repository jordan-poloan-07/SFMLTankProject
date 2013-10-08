
#ifndef TANKS
#define TANKS

#include "Utility.h"

using namespace std;
using namespace sf;
using UtilMath::radianForm;

class GameChar
{
public:
	GameChar()
	{
		sprite = NULL;
		centerX = centerY = dX = dY = 0.0f;
	}

	virtual ~GameChar()
	{
		delete sprite;
	}

	float getCenterX() const
	{
		return centerX;
	}

	float getCenterY() const
	{
		return centerY;
	}

	Sprite* getSprite() const
	{
		return sprite;
	}

	virtual void update() = 0;

protected:
	float centerX, centerY, dX, dY;
	Sprite* sprite;
};

class Rocket : public GameChar
{
public:
	Rocket(Sprite* sp, float centerX, float centerY, float theta)
	{
		rocketRelease = 76.0f;

		this->centerX = centerX + rocketRelease * cosf(radianForm(theta));
		this->centerY = centerY + rocketRelease * sinf(radianForm(theta));
		this->theta = theta;
		this->isVisible = true;

		this->sprite = sp;
		this->dX = 5 * cosf(radianForm(theta));
		this->dY = 5 * sinf(radianForm(theta));
	}

	float getTheta() const
	{
		return theta;
	}

	float getVisible() const
	{
		return isVisible;
	}

	void setVisible(bool isVisible)
	{
		this->isVisible = isVisible;
	}

	void update()
	{
		centerX += dX;
		centerY += dY;

		if (centerX < 0 || centerY > 0 ||centerX > 800 || centerY > 600 )
		{
			setVisible(false);
		}

		sprite->setPosition(centerX, centerY);
		sprite->setRotation(theta);
	}

private:
	bool isVisible;
	float theta, rocketRelease;
};

class Tanks : public GameChar
{
public:
	Tanks(Sprite* spbody, Sprite* spweap, Sprite* tankRocket, float x, float y) 
	{
		this->sprite = spbody;
		this->weapSpr = spweap;
		this->tankRocket = tankRocket;

		bodyTheta = weapTheta = bThetaIncr = wThetaIncr = 0.0f;

		centerX = x;
		centerY = y;
	}

	~Tanks()
	{
		delete weapSpr;

		for(unsigned int i = 0; i < rockets.size(); i++)
		{
			delete rockets[i];
		}
	}

	Sprite* getSprite2() const
	{
		return weapSpr;
	}

	// can be changed
	vector<Rocket*> getRockets()
	{
		return rockets;
	}

	void weaponShoot()
	{
		rockets.push_back(new Rocket(new Sprite(*tankRocket), centerX, centerY, weapTheta));
	}

	void moveWeapCCW()
	{
		wThetaIncr = -1.0f;
	}

	void moveWeapCW()
	{
		wThetaIncr = 1.0f;
	}

	void moveBodyCCW()
	{
		bThetaIncr = -0.5f;
		wThetaIncr = -0.5f;
	}

	void moveBodyCW()
	{
		bThetaIncr = 0.5f;
		wThetaIncr = 0.5f;
	}

	void stopWeap()
	{
		wThetaIncr = 0.0f;
	}

	void stopBody()
	{
		bThetaIncr = 0.0f;
		stopWeap();
	}

	void forward()
	{
		dX = cosf(radianForm(bodyTheta));
		dY = sinf(radianForm(bodyTheta));
	}

	void backward()
	{
		dX = -cosf(radianForm(bodyTheta));
		dY = -sinf(radianForm(bodyTheta));
	}

	void stop()
	{
		dX = dY = 0.0f;
	}

	void update()
	{
		if( weapTheta < 360 || weapTheta > -360 )
			weapTheta += wThetaIncr;
		else 
			weapTheta = 0;

		if( bodyTheta < 360 || bodyTheta > -360 )
			bodyTheta += bThetaIncr;
		else 
			bodyTheta = 0;

		cout << bodyTheta << " " << weapTheta << endl;

		centerX += dX;
		centerY += dY;

		this->sprite->setRotation(bodyTheta);
		this->weapSpr->setRotation(weapTheta);

		this->weapSpr->setPosition(centerX,centerY);
		this->sprite->setPosition(centerX,centerY);

		for(unsigned int i = 0; i < rockets.size(); i++)
		{
			rockets[i]->update();
		}
	}

private:
	float bodyTheta, weapTheta, bThetaIncr, wThetaIncr;
	Sprite* weapSpr; // the sprite inherited will be used for body sprite
	Sprite* tankRocket;
	vector<Rocket*> rockets;
};

#endif