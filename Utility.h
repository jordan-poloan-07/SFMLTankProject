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

#endif