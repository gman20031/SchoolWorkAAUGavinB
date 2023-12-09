#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "../Menu.h"
#include "../LocationAndDirection.h"

class levelInfo
{
	char** m_pCharMapArray;
	int m_mapWidth;
	int m_mapHeight;
	Location m_selectedChar = { -1,-1 };

	static bool PrintRed(char printedChar);

public:
	static constexpr char kWallChar = '#';
	static constexpr char kEmptySpaceChar = '.';
	static constexpr char kTrapChar = 'O';

	void FillFromFile(const char* filePath);

	levelInfo();
	levelInfo(int width, int height);
	levelInfo(levelInfo& copiedLevel);
	~levelInfo();

	void InitMap(int width, int height);
	char GetAt(Location targetLocation) const;
	void SetAt(Location targetLocation, char newChar);
	int GetMapWidth() const;
	int GetMapHeight() const;

	Location GetSelectedLocation() const;
	void MoveCursor(Direction dir);
	void SetCursor(Location& newLoc);
	void SetCursor(int x, int y);

	void Display() const;
	void DisplayNoSelect() const;
	void WriteToFile(std::ofstream& file) const;

	void EnsureInBounds(Location& targetlocation);
};