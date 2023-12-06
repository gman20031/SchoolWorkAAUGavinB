#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

#include "Level/LevelData.h"
#include "Menu.h"
#include "LevelEditMenu.h"

constexpr int kSpecialWindowsKey = -32;

static location HandleArrowKey(location currLocation);
const bool PrintRedString(std::string printedString);
static const void PrintLevelEditor(levelInfo& levelOne);

location MapTarget = { 0,0 };
location cursorLocation = { 0,0 };
std::string test1 = "| testOne |";
std::string test2 = "| two |";
std::string test3 = "| three |";
std::string test4 = "| four |";
bool inMap = false;

int main(int argc, char* argv[])
{
	levelInfo levelOne(4,4);

	std::string name = "urdum";
	WallSelector wallSelectButton(name);
	wallSelectButton.DisplayText();

	//for (;;)
	//{
	//	PrintLevelEditor(levelOne);

	//	char inputChar = _getch();
	//	if (inputChar == kSpecialWindowsKey)
	//	{
	//		if(cursorLocation.y == 1)
	//		{
	//			MapTarget = HandleArrowKey(MapTarget);
	//			if (MapTarget.y == levelOne.GetMapHeight())
	//				cursorLocation.y += 1;
	//			if (MapTarget.y < 0)
	//				cursorLocation.y -= 1;
	//			levelOne.EnsureInBounds(MapTarget);
	//		}
	//		else
	//		{
	//			cursorLocation = HandleArrowKey(cursorLocation);
	//		}
	//	}
	//	system("cls");
	//}
	
	
	return 0;
}

static const void PrintLevelEditor(levelInfo& levelOne)
{
	if (cursorLocation.y == 0)
	{
		if (cursorLocation.x == 0)
		{
			PrintRedString(test1);
			std::cout << test2;
		}
		if (cursorLocation.x == 1)
		{
			std::cout << test1;
			PrintRedString(test2);
		}
		std::cout << std::endl;
	}
	else
		std::cout << test1 << test2 << std::endl;

	if (cursorLocation.y == 1)
		levelOne.PrintSelect(MapTarget);
	else
		levelOne.PrintNoSelect();

	if (cursorLocation.y == 2)
	{
		if (cursorLocation.x == 0)
		{
			PrintRedString(test3);
			std::cout << test4;
		}
		if (cursorLocation.x == 1)
		{
			std::cout << test3;
			PrintRedString(test4);
		}
		std::cout << std::endl;
	}
	else
		std::cout << test3 << test4 << std::endl;
}

const bool PrintRedString(std::string printedString)
{
	constexpr int kRedConsoleColor = 4;
	constexpr int kStandardConsoleColor = 7;

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, kRedConsoleColor);
	std::cout << printedString;
	SetConsoleTextAttribute(consoleHandle, kStandardConsoleColor);
	return true;
}

static location HandleArrowKey(location currLocation)
{
	enum arrowKeys {
		right = 77,
		down = 80,
		up = 72,
		left = 75
	};

	char dummyChar = _getch();
	switch (dummyChar)
	{
	case arrowKeys::right:
		++currLocation.x;
		break;
	case arrowKeys::down:
		++currLocation.y;
		break;
	case arrowKeys::up:
		--currLocation.y;
		break;
	case arrowKeys::left:
		--currLocation.x;
		break;
	}
	return currLocation;
}