#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "Character.h"

using namespace sf;
using namespace std;

// two pointers
Sprite* createSprite(string filename, float xOrigin, float yOrigin)
{
	Texture* t = new Texture(); // needs to deleted
	t->loadFromFile(filename);

	Sprite* s = new Sprite(*t);

	s->setOrigin(xOrigin, yOrigin);

	return s;
}

int main()
{
	RenderWindow rw(VideoMode(800,600),"The Tank");
	Event evt;

	float centerX, centerY;
	bool gameIsRunning = true;

	centerX = 200.0f;
	centerY = 300.0f;

	Sprite* tankBodySpr;
	Sprite* tankWpnSpr; 
	Sprite* tankRocket;

	tankBodySpr = createSprite("tanks/tankbody_64_40.png", 64, 40);
	tankWpnSpr = createSprite("tanks/tankwpn_18_21_76.png", 18, 21);
	tankRocket = createSprite("tanks/rocket_13_12.png", 13, 12);

	Tanks tank(tankBodySpr, tankWpnSpr, tankRocket, centerX, centerY);

	while(gameIsRunning)
	{
		while(rw.pollEvent(evt))
		{
			switch(evt.type)
			{
			case Event::Closed:
				{
					rw.close();
					gameIsRunning = false;
					break;
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

		tank.update();

		rw.clear();

		for(unsigned int i = 0; i < tank.getRockets().size(); i++)
		{
			rw.draw( *( tank.getRockets() )[i]->getSprite() );
		}

		rw.draw(*tank.getSprite());
		rw.draw(*tank.getSprite2());
		rw.display();

		sf::sleep(Time(milliseconds(16)));

	}

	return 0;
}