#include <SFML/Graphics.hpp>
#include <iostream>

#include "Character.h"
#include "Animation.h"
#include "Manager.h"

using namespace sf;
using namespace std;

/**
void drawRocket(RenderWindow& rw, Sprite sp, float centerX, float centerY, float theta)
{
sp.setPosition(centerX,centerY);
sp.setRotation(theta);
rw.draw(sp);
}
**/

void DetectInput(Event& evt, Tanks& tank)
{
	switch(evt.key.code)
	{
	case Keyboard::Q:
		if( evt.type == Event::KeyPressed )
			tank.moveWeapCCW();
		else
			tank.stopWeap();
		break;
	case Keyboard::E:
		if( evt.type == Event::KeyPressed )
			tank.moveWeapCW();
		else
			tank.stopWeap();
		break;
	case Keyboard::A:
		if( evt.type == Event::KeyPressed )
			tank.moveBodyCCW();
		else
			tank.stopBody();

		break;
	case Keyboard::D:
		if( evt.type == Event::KeyPressed )
			tank.moveBodyCW();
		else
			tank.stopBody();

		break;
	case Keyboard::W:
		if( evt.type == Event::KeyPressed )
			tank.forward();
		else
			tank.stop();

		break;
	case Keyboard::S:
		if( evt.type == Event::KeyPressed )
			tank.backward();
		else
			tank.stop();

		break;
	case Keyboard::X:
		if( evt.type == Event::KeyPressed )
			tank.weaponShoot();		
		break;
	}
}

bool CollDetect(GameChar& a, GameChar& b)
{

	float topA = a.getBounds().top;
	float bottomA = a.getBounds().top + a.getBounds().height ;
	float leftA = a.getBounds().left;
	float rightA = a.getBounds().left + a.getBounds().width;

	float topB = b.getBounds().top;
	float bottomB = b.getBounds().top + b.getBounds().height;
	float leftB = b.getBounds().left;
	float rightB = b.getBounds().left + b.getBounds().width;

	if( bottomA < topB )
	{
		return false;
	}

	if( topA > bottomB )
	{
		return false;
	}

	if( rightA < leftB )
	{
		return false;
	}

	if( leftA > rightB )
	{
		return false;
	}

	return true;

}

int main()
{
	RenderWindow rw( VideoMode(800,600), "The Violent Tank");
	Event evt;

	float centerX, centerY;
	bool gameIsRunning = true;

	centerX = 200.0f;
	centerY = 300.0f;

	Texture bodyTank, weapTank, rocketTank, exp1, exp2, exp3, exp4, exp5;
	bodyTank.loadFromFile("tanks/tankbody_64_40.png");
	weapTank.loadFromFile("tanks/tankwpn_18_21_76.png");
	rocketTank.loadFromFile("tanks/rocket_13_12.png");
	exp1.loadFromFile("tanks/exp1.png");
	exp2.loadFromFile("tanks/exp2.png");
	exp3.loadFromFile("tanks/exp3.png");
	exp4.loadFromFile("tanks/exp4.png");
	exp5.loadFromFile("tanks/exp5.png");

	Sprite tankBodySpr(bodyTank);
	tankBodySpr.setOrigin(64, 40);
	Sprite tankWpnSpr(weapTank);
	tankWpnSpr.setOrigin(18, 21);

	Sprite expl1(exp1);
	expl1.setOrigin(59,59);
	Sprite expl2(exp2);
	expl2.setOrigin(59,59);
	Sprite expl3(exp3);
	expl3.setOrigin(59,59);
	Sprite expl4(exp4);
	expl4.setOrigin(59,59);
	Sprite expl5(exp5);
	expl5.setOrigin(59,59);

	Tanks tank(tankBodySpr, tankWpnSpr, rocketTank, centerX, centerY);

	vector<Enemy> enemies;
	enemies.push_back(Enemy(100.0f,100.0f,25.0f));
	enemies.push_back(Enemy(150.0f,150.0f,25.0f));
	enemies.push_back(Enemy(200.0f,200.0f,25.0f));

	vector<AnimFrame> defaultExplFrames;
	defaultExplFrames.push_back( AnimFrame( expl1, 50 ) );
	defaultExplFrames.push_back( AnimFrame( expl2, 50 ) );
	defaultExplFrames.push_back( AnimFrame( expl3, 50 ) );
	defaultExplFrames.push_back( AnimFrame( expl4, 50 ) );
	defaultExplFrames.push_back( AnimFrame( expl5, 50 ) );

	vector<Animation> explosionAnimations;

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
			}

			DetectInput(evt, tank);
		}

		/** UPDATES

		**/

		// updating
		tank.update();

		for_each( enemies.begin(), enemies.end(), []( Enemy& e ){ e.update(); } );

		for_each( explosionAnimations.begin(), explosionAnimations.end(), []( Animation& a ) { a.update(25); } );

		auto iter = remove_if(enemies.begin(),enemies.end(), []( Enemy& e) { return ! e.getVisible(); } );
		enemies.erase( iter, enemies.end() );

		auto iter2 = remove_if(explosionAnimations.begin(),explosionAnimations.end(), []( Animation& a) { return a.getIsAnimFin(); } );
		explosionAnimations.erase( iter2, explosionAnimations.end() );

		// rockets and enemies collision detection
		if ( tank.getRockets()->size() > 0 )
		{
			for(size_t i = 0 ; i < tank.getRockets()->size(); i++)
			{
				for(size_t j = 0; j < enemies.size(); j++)
				{
					if( CollDetect( tank.getRockets()->at(i) , enemies[j] ) )
					{
						tank.getRockets()->at(i).setInvisible();
						enemies[j].setInvisible();

						explosionAnimations.push_back( Animation( enemies[j].getCenterX(), 
							enemies[j].getCenterY(), 
							defaultExplFrames ) );
					}
				}
			}

		}

		/** DISPLAY

		**/

		rw.clear();

		// for tank rockets drawing
		auto tankRs = tank.getRockets();
		for_each(tankRs->begin(), tankRs->end(), [&]( Rocket& r ){ rw.draw( r.getSprite() ); } );

		// for enemies drawing
		for_each( enemies.begin(), enemies.end(), [&]( Enemy& e ){ rw.draw( e.getSprite() ); } );
 
		// for explosion animations drawing
		for_each( explosionAnimations.begin(), explosionAnimations.end(), [&]( Animation& a ){ rw.draw( a.getSprite() ); } );

		rw.draw(*tank.getSprite());
		rw.draw(*tank.getSprite2());

		rw.display();

		sf::sleep(Time(milliseconds(16)));

	}

	return 0;
}