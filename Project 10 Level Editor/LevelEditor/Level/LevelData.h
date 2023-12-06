#pragma once

#include <vector>

struct location
{
	int x;
	int y;
};

class levelInfo
{
	char** m_pCharMapArray;
	int m_mapWidth;
	int m_mapHeight;
	
	static bool PrintRed(char printedChar);

public:
	static constexpr char kWallChar = '#';
	static constexpr char kEmptySpaceChar = '.';
	static constexpr char kTrapChar = 'O';

	levelInfo();
	levelInfo(int width, int height);
	levelInfo(levelInfo& copiedLevel);
	~levelInfo();

	//void initMap(char** map); this is bad, I cannot easily get the height/width from this
	void InitMap(int width, int height);
	char GetAt(location targetLocation);
	void SetAt(location targetLocation, char newChar);
	int GetMapWidth();
	int GetMapHeight();

	void PrintSelect(location selectedLocation);
	void PrintNoSelect();

	void EnsureInBounds(location& targetlocation);
};