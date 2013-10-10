#include <SFML/Graphics.hpp>
#include <iostream>

#include "Character.h"

#include <crtdbg.h>

using namespace sf;
using namespace std;

void drawRocket(RenderWindow& rw, Sprite sp, float centerX, float centerY, float theta)
{
	sp.setPosition(centerX,centerY);
	sp.setRotation(theta);
	rw.draw(sp);
}

int main()
{

	RenderWindow rw(VideoMode(800,600),"The Tank");
	Event evt;

	float centerX, centerY;
	bool gameIsRunning = true;

	centerX = 200.0f;
	centerY = 300.0f;

	
	Texture bodyTank, weapTank, rocketTank;

	bodyTank.loadFromFile("tanks/tankbody_64_40.png");

	weapTank.loadFromFile("tanks/tankwpn_18_21_76.png");

	rocketTank.loadFromFile("tanks/rocket_13_12.png");
	

	/**
	Texture *bodyTank, *weapTank, *rocketTank;

	bodyTank = new Texture;
	bodyTank->loadFromFile("tanks/tankbody_64_40.png");

	weapTank = new Texture;
	weapTank->loadFromFile("tanks/tankwpn_18_21_76.png");

	rocketTank = new Texture;
	rocketTank->loadFromFile("tanks/rocket_13_12.png");
	**/

	Sprite tankBodySpr(bodyTank);
	tankBodySpr.setOrigin(64, 40);
	Sprite tankWpnSpr(weapTank);
	tankWpnSpr.setOrigin(18, 21); 
	Sprite tankRocket(rocketTank);
	tankRocket.setOrigin(13, 12);

	Tanks tank(centerX, centerY);

	while(gameIsRunning)
	{
		
		/** INPUTS

		**/

		while(rw.pollEvent(evt))
		{
			switch(evt.type)
			{
			case Event::Closed:
				{
					gameIsRunning = false;
				}
				break;
			case Event::KeyPressed:

				switch(evt.key.code)
				{
				case Keyboard::Q:
					tank.moveWeapCCW();
					break;
				case Keyboard::E:
					tank.moveWeapCW();
					break;
				case Keyboard::A:
					tank.moveBodyCCW();
					break;
				case Keyboard::D:
					tank.moveBodyCW();
					break;
				case Keyboard::W:
					tank.forward();
					break;
				case Keyboard::S:
					tank.backward();
					break;
				case Keyboard::X:
					tank.weaponShoot();
					break;
				}

				break;
			case Event::KeyReleased:

				switch(evt.key.code)
				{
				case Keyboard::Q:
					tank.stopWeap();
					break;
				case Keyboard::E:
					tank.stopWeap();
					break;
				case Keyboard::A:
					tank.stopBody();
					break;
				case Keyboard::D:
					tank.stopBody();
					break;
				case Keyboard::W:
					tank.stop();
					break;
				case Keyboard::S:
					tank.stop();
					break;
				case Keyboard::X:
					break;
				}

				break;
			}
		}

		/** UPDATES

		**/

		tank.update();

		// update the sprite's properties

		tankBodySpr.setPosition(tank.getCenterX(),tank.getCenterY());
		tankWpnSpr.setPosition(tank.getCenterX(),tank.getCenterY());

		tankBodySpr.setRotation(tank.getBodyTheta());
		tankWpnSpr.setRotation(tank.getWeapTheta());

		//


		/** DISPLAY

		**/

		rw.clear();

		for(unsigned int i = 0; i < tank.getRockets().size(); i++)
		{
			// so much pass by value here
			drawRocket(rw, tankRocket, (tank.getRockets())[i]->getCenterX(), (tank.getRockets())[i]->getCenterY(), (tank.getRockets())[i]->getTheta());
		}

		rw.draw(tankBodySpr);
		rw.draw(tankWpnSpr);
		rw.display();

		sf::sleep(Time(milliseconds(16)));

	}

	_CrtDumpMemoryLeaks();

	return 0;
}