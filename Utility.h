#ifndef UTILITY
#define UTILITY

#include <SFML/Graphics.hpp>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;
using namespace sf;


float radianForm(float degree)
{
	return ( degree * 3.1415926545f / 180.0f );
}


#endif