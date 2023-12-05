#include "Level/LevelData.h"
#include <iostream>

char levelInfo::get(location targetLocation)
{
	return 0;
}

void levelInfo::set(location targetLocation, char newChar)
{

}

void levelInfo::print(location selectedLocation)
{
	//test values
	int height = 4;
	int width = 10;

	for (int i = 0; i < height; ++i)
	{
		for (int n = 0; n < width; ++n)
		{
			std::cout << charMapArray[i][n];
		}
		std::cout << std::endl;
	}

}

void levelInfo::initMap(char** map)
{
	charMapArray = map;
}