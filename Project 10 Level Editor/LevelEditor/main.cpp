#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Level/LevelData.h"

constexpr int g_kRedConsoleColor = 7;
constexpr int g_kStandardConsoleColor = 4;

int main(int argc, char* argv[])
{
	levelInfo levelOne;

	int height = 4;
	int width = 10;

	char** dummMap = new char*[height];
	char* ptr = *dummMap;
	for (int i = 0; i < height; ++i)
	{
		char* dummyArray = new char[width + 1];
		dummyArray[width] = '\0';
		for (int w = 0; w < width; ++w)
		{
			dummyArray[w] = '#';
		}
		++ptr;
	}

	levelOne.initMap(dummMap);
	levelOne.print({ 0,0 });

	//int selectedCharacter = 5;
	//for(;;)
	//{
	//	system("cls");
	//	for (int i = 0; i < length; ++i)
	//	{
	//		if (i % mapwidth == 0)
	//			std::cout << std::endl;

	//		if (i == selectedCharacter)
	//			PrintRed(MAPTEST[i]);
	//		else
	//			std::cout << MAPTEST[i];
	//	}
	//	
	//	char dummyChar = _getch();
	//	if (dummyChar == kspecialWindowsInput)
	//		selectedCharacter = HandleArrowKey(selectedCharacter);
	//}
	return 0;
}

int HandleArrowKey(int currIndex)
{
	enum arrowKeys {
		right = 77,
		down = 80,
		up = 72,
		left = 75
	};

	char dummyChar = _getch();
	switch(dummyChar)
	{
	case arrowKeys::right:
		++currIndex;
		break;
	case arrowKeys::down:
		currIndex += 6;
		break;
	case arrowKeys::up:
		currIndex -= 6;
		break;
	case arrowKeys::left:
		--currIndex;
		break;
	}
	return currIndex;
}

bool PrintRed(char printedChar)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, g_kRedConsoleColor);
	std::cout << printedChar;
	SetConsoleTextAttribute(consoleHandle, g_kStandardConsoleColor);
	return true;
}