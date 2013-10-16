
#ifndef TANKS
#define TANKS

#include "Utility.h"

using namespace std;
using namespace sf;

class GameChar
{
public:
	GameChar()
	{
		centerX = centerY = dX = dY = 0.0f;
	}

	virtual ~GameChar()
	{

	}

	float getCenterX() const
	{
		return centerX;
	}

	float getCenterY() const
	{
		return centerY;
	}

	float getDx() const
	{
		return dX;
	}

	float getDy() const
	{
		return dY;
	}

	bool getVisible() const
	{
		return isVisible;
	}

	void setInvisible()
	{
		this->isVisible = false;
	}

	virtual void update() = 0;
	virtual FloatRect getBounds() const = 0;

protected:
	float centerX, centerY, dX, dY;	
	bool isVisible;
};

class Rocket : public GameChar
{
public:
	Rocket(Sprite sp, float centerX, float centerY, float theta)
	{
		cout << "Rocket Created" << endl;
		float rocketRelease = 76.0f;

		this->centerX = centerX + rocketRelease * cosf(radianForm(theta));
		this->centerY = centerY + rocketRelease * sinf(radianForm(theta));
		this->isVisible = true;

		this->theta = theta;
		this->dX = 5 * cosf(radianForm(theta));
		this->dY = 5 * sinf(radianForm(theta));

		this->rocketSprite = sp;
	}

	~Rocket()
	{
		cout <<"Rocket deleted"<<endl;
	}

	float getTheta() const
	{
		return theta;
	}

	Sprite getSprite() const
	{
		return rocketSprite;
	}

	FloatRect getBounds() const
	{
		return rocketSprite.getGlobalBounds();
	}

	void update()
	{
		centerX += dX;
		centerY += dY;

		if (centerX < 0 || centerY < 0 ||centerX > 800 || centerY > 600 )
		{
			setInvisible();
		}

		rocketSprite.setPosition(centerX,centerY);
		rocketSprite.setRotation(theta);

	}

private:
	float theta;
	Sprite rocketSprite;
};

class Enemy : public GameChar 
{
public:
	Enemy(float x, float y, float radius)
	{
		this->centerX = x;
		this->centerY = y;

		cs = CircleShape(radius);
		cs.setOrigin(radius , radius);
		cs.setFillColor(Color::Blue);
		cs.setPosition(x,y);

		dX = 2.0f;
	}

	CircleShape getSprite() const
	{
		return cs;
	}

	FloatRect getBounds() const 
	{
		return cs.getGlobalBounds();
	}

	void update()
	{
		if( centerX > 600 )
		{
			dX = -2.0f;
		}
		else if( centerX < 200 )
		{
			dX = 2.0f;
		}

		centerX += dX;

		cs.setPosition(centerX,centerY);
	}


private:
	CircleShape cs;
};

class Tanks : public GameChar
{
public:
	Tanks(Sprite sprite, Sprite sprite2, Texture rocketTexture, float x, float y) 
	{
		rockets = new vector<Rocket>;

		bodyTheta = weapTheta = bThetaIncr = wThetaIncr = 0.0f;

		centerX = x;
		centerY = y;

		this->sprite = new Sprite(sprite);
		this->sprite2 = new Sprite(sprite2);
		this->rocketTexture = rocketTexture;
	}

	~Tanks()
	{
		delete rockets;
		delete sprite;
		delete sprite2;
	}

	float getBodyTheta() const
	{
		return bodyTheta;
	}

	float getWeapTheta() const
	{
		return weapTheta;
	}

	// can be changed
	vector<Rocket>* getRockets()
	{
		return rockets;
	}


	Sprite* getSprite() const
	{
		return sprite;
	}

	Sprite* getSprite2() const
	{
		return sprite2;
	}

	FloatRect getBounds() const
	{
		return sprite->getGlobalBounds();
	}

	void weaponShoot()
	{
		Sprite sp;
		sp.setTexture(rocketTexture);
		sp.setOrigin(13,12);
		rockets->push_back( Rocket(sp, centerX, centerY, weapTheta ) );
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

		cout << rockets->size() << " " << endl;

		centerX += dX;
		centerY += dY;

		sprite->setPosition(centerX,centerY);
		sprite2->setPosition(centerX,centerY);

		sprite->setRotation(bodyTheta);
		sprite2->setRotation(weapTheta);

		for(unsigned int i = 0; i < rockets->size(); i++)
		{
			(*rockets)[i].update();
		}

		if( rockets->size() >= 1 )
		{
			auto iter = remove_if(rockets->begin(), rockets->end(), []( const Rocket& r) { return ! r.getVisible(); } );
			rockets->erase( iter, rockets->end() );
		}


	}

private:
	float bodyTheta, weapTheta, bThetaIncr, wThetaIncr;
	vector<Rocket>* rockets;
	Sprite* sprite;
	Sprite* sprite2;
	Texture rocketTexture;
};

#endif