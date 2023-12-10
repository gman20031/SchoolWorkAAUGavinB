#include "../Header/Inputs.h"

#include <conio.h>
#include <iostream>

#include "../../Editor.h"
#include "../../Game.h"


void Inputs::HandleArrowKey(Location* Location)
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
		++Location->x; break;
	case arrowKeys::down:
		++Location->y; break;
	case arrowKeys::up:
		--Location->y; break;
	case arrowKeys::left:
		--Location->x; break;
	}
}

Direction Inputs::GetDirFromArrowKey()
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
		return Direction::kRight;
	case arrowKeys::down:
		return Direction::kDown;
	case arrowKeys::up:
		return Direction::kUp;
	case arrowKeys::left:
		return Direction::kLeft;
	default:
		return Direction::kLeft;
	}
}

void Inputs::MoveLocation(Location* Location , Direction dir )
{
	switch (dir)
	{
	case Direction::kDown:
		++Location->y; break;
	case Direction::kUp:
		--Location->y; break;
	case Direction::kLeft:
		--Location->x; break;
	case Direction::kRight:
		++Location->x; break;
	}
}


int Inputs::GetMeAnInt()
{
	int userIntInput;
	std::cin >> userIntInput;

	while (!std::cin.good())
	{
		std::cout << "Please enter an integer only \n";
		std::cin.clear();													
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> userIntInput;
	}
	return userIntInput;
}


bool Inputs::SetStringFromUser(std::string& str)
{
	std::cin >> str;

	if (!std::cin.good())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return true;;
	}

}