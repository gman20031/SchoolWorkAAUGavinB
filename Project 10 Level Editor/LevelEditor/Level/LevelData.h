#pragma once

struct location
{
	int x;
	int y;
};

class levelInfo
{
	char** charMapArray;
public:
	void initMap(char** map);

	char get(location targetLocation);
	void set(location targetLocation, char newChar);
	void print(location selectedLocation);
};