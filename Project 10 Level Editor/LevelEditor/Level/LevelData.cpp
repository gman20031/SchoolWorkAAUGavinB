#include "LevelData.h"
#include <iostream>
#include <windows.h>

/////////////////////////////////////////////////
/// Construct / deconstruct
/////////////////////////////////////////////////

levelInfo::levelInfo() 
{
	InitMap(1, 1);

}
levelInfo::levelInfo(int width, int height)
{
	InitMap(width, height);
}

levelInfo::levelInfo(levelInfo& copiedLevel)
{
	InitMap(copiedLevel.GetMapWidth(), copiedLevel.GetMapHeight());
	for (int y = 0; y < m_mapHeight; ++y)
	{
		for (int x = 0; x < m_mapWidth; ++x)
		{
			SetAt({ x,y }, copiedLevel.GetAt({ x,y }));
		}
	}
}

levelInfo::~levelInfo()
{
	for (int y = 0; y < m_mapHeight; ++y)
	{
		delete[] m_pCharMapArray[y];
	}
	delete[] m_pCharMapArray;
}

/////////////////////////////////////////////////
/// Map Array Managment
/////////////////////////////////////////////////

int levelInfo::GetMapWidth()
{
	return m_mapWidth;
}
int levelInfo::GetMapHeight()
{
	return m_mapHeight;
}

char levelInfo::GetAt(location targetLocation)
{
	return m_pCharMapArray[targetLocation.y][targetLocation.x];
}

void levelInfo::SetAt(location targetLocation, char newChar)
{
	m_pCharMapArray[targetLocation.y][targetLocation.x] = newChar;
}

void levelInfo::InitMap(int width, int height)
{
	m_mapWidth = width;
	m_mapHeight = height;

	char** tempMap = new char* [height];
	for (int i = 0; i < height; ++i)
	{
		tempMap[i] = new char[width + 1];
	}
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			tempMap[y][x] = kWallChar;
		}
		tempMap[y][width] = '\0';
	}
	m_pCharMapArray = tempMap;
}

/////////////////////////////////////////////////
/// Printing Functions
/////////////////////////////////////////////////

void levelInfo::PrintSelect(location selectedLocation)
{
	for (int y = 0; y < m_mapHeight; ++y)
	{
		for (int x = 0; x < m_mapWidth; ++x)
		{
			if (selectedLocation.x == x and selectedLocation.y == y)
			{
				PrintRed(m_pCharMapArray[y][x]);
				std::cout << ' ';
			}
			else
				std::cout << m_pCharMapArray[y][x] << ' ';
		}
		std::cout << std::endl;
	}

}

void levelInfo::PrintNoSelect()
{

	for (int y = 0; y < m_mapHeight; ++y)
	{
		for (int x = 0; x < m_mapWidth; ++x)
		{
			std::cout << m_pCharMapArray[y][x];
			std::cout << ' ';
		}
		std::cout << std::endl;
	}

}

bool levelInfo::PrintRed(char printedChar)
{
	constexpr int kRedConsoleColor = 4;
	constexpr int kStandardConsoleColor = 7;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, kRedConsoleColor);
	std::cout << printedChar;
	SetConsoleTextAttribute(consoleHandle, kStandardConsoleColor);
	return true;
}

/////////////////////////////////////////////////
/// Other Functions
/////////////////////////////////////////////////

void levelInfo::EnsureInBounds(location& targetlocation)
{
	if (targetlocation.x > m_mapWidth-1) // magic -1's because  width = number of elements
		targetlocation.x = m_mapWidth-1; // not the highest index value (so off by 1)
	if (targetlocation.x < 0)
		targetlocation.x = 0;
	if (targetlocation.y > m_mapHeight-1)
		targetlocation.y = m_mapHeight-1;
	if (targetlocation.y < 0)
		targetlocation.y = 0;
}