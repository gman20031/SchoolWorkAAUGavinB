#include <iostream>
#include <windows.h>
#include <string>

#include "LevelData.h"
#include "../Inputs.h"
#include "../Menu.h"

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

int levelInfo::GetMapWidth() const
{
	return m_mapWidth;
}
int levelInfo::GetMapHeight() const 
{
	return m_mapHeight;
}


char levelInfo::GetAt(Location targetLocation) const
{
	return m_pCharMapArray[targetLocation.y][targetLocation.x];
}

void levelInfo::SetAt(Location targetLocation, char newChar)
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

// Print the level with the selected char in red
void levelInfo::Display() const
{

	for (int y = 0; y < m_mapHeight; ++y)
	{
		for (int x = 0; x < m_mapWidth; ++x)
		{
			if ( (m_selectedChar.x == x) and (m_selectedChar.y == y) )
				PrintRed(m_pCharMapArray[y][x]);
			else
				std::cout << m_pCharMapArray[y][x];
			std::cout << ' ';
		}
		std::cout << std::endl;
	}

}

// Print the map with no red text
void levelInfo::DisplayNoSelect() const
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
 
// Writes the map to given File
void levelInfo::WriteToFile(std::ofstream& file) const
{

	for (int y = 0; y < m_mapHeight; ++y)
	{
		for (int x = 0; x < m_mapWidth; ++x)
		{
			file << m_pCharMapArray[y][x];
			file << ' ';
		}
		file << std::endl;
	}

}

bool levelInfo::PrintRed(char printedChar)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, Menu::kRedColor);
	std::cout << printedChar;
	SetConsoleTextAttribute(consoleHandle, Menu::kStandarColor);
	return true;
}

/////////////////////////////////////////////////
/// Cursor Functions
/////////////////////////////////////////////////

Location levelInfo::GetSelectedLocation() const
{
	return m_selectedChar;
}

void levelInfo::MoveCursor(Direction dir)
{
	Inputs::MoveLocation(&m_selectedChar, dir);
}

void levelInfo::SetCursor(Location& newLoc)
{
	m_selectedChar = newLoc;
}
void levelInfo::SetCursor(int x, int y)
{
	m_selectedChar.x = x;
	m_selectedChar.y = y;
}

/////////////////////////////////////////////////
/// Other Functions
/////////////////////////////////////////////////

void levelInfo::EnsureInBounds(Location& targetlocation)
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

void levelInfo::FillFromFile(const char* filePath)
{
	constexpr char kSpace = ' ';
	constexpr char kTab = '	';
	constexpr char kNewLine = '\n';

	bool widthFound = false;
	int width = 0;
	int height = 0;

	std::fstream myFile;
	myFile.open(filePath);
	if (myFile.is_open())
	{
		char tempChar;
		while (!myFile.eof()) // first pass
		{
			myFile >> tempChar;
			if (!widthFound)
			{
				if (tempChar != kSpace or tempChar != kTab or tempChar != kNewLine)
				{
					++width;
				}
			}
			if (tempChar == kNewLine)
			{
				++height;
				widthFound = true;
			}
		}
		myFile.seekp(std::ios_base::beg);
		InitMap(width, height);
		width = 0;
		height = 0;
		while (!myFile.eof()) // fill pass
		{
			myFile >> tempChar;
			if (tempChar != kSpace or tempChar != kTab or tempChar != kNewLine)
			{
				SetAt({ width, height }, tempChar);
				++width;
			}
			if (tempChar == kNewLine)
			{
				++height;
			}
		}
		myFile.close();
	}
	else
	{
		std::cout << "your -redacted- trash lol ";
	}
}