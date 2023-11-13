/* Summary of Game

Summary:
The user moves through a maze of walls to find an exit.

Game Specification:
    The user sees the maze in the form of a grid of tiles, with a size of at least 8 x 8.
    Use the '.' character to represent an empty tile.
    Use the '@' character to represent the player character's current position.
    Use the '#' character to represent a wall. The player cannot move through a wall.
    Use the 'X' character to represent the exit. When the player touches this, the game ends in a win.
	use the '!' character to represent enemy. Get sent to the beginning if the player touches the enemy.
	use the 'O' character to represent a trap. Get sent to the beginning if the player touches the trap.
    Do not allow the player character to move off the edges of the map.

	Moving enemies
	Traps
	Multiple Levels (6?)

*/

#include <iostream>
#include <vector>
#include <fstream> // for filereading
#include <locale>  // for upper Casing
#include <conio.h> // _getch()
#include "levels.h" // structs and getting level info from file

#define myPrint(str) std::cout << str << std::endl

class enemy 
{
	location loc_start;
	location loc_current;
	unsigned int currentDirection = 0;
	enum directions
	{
		up = 0,
		right = 1,
		down = 2,
		left = 3,
	};
	unsigned short int currentLoop = 0;
	enum loopType
	{
		horizontal = '|',
		verticle = '-',
	};
	
public:
};

void ChangePlayerPosition(levelInfo* curLevel, int x, int y);
void UpdatePlayer(levelInfo* curLevel, std::vector<levelInfo>* allLevels, int x, int y);
void MovePlayer(levelInfo* curLevel, std::vector<levelInfo>* allLevels, char input);
void ChangeLevel(levelInfo* curLevel, std::vector<levelInfo>* allLevels, char input);
void ResetLevel(levelInfo* curLevel);
bool ProcessInput(levelInfo* curLevel, std::vector<levelInfo>* allLevels, char input);

int main()
{
	std::vector<levelInfo> allLevels = GetAllLevels();

	levelInfo curLevel = allLevels.at(0);

	char input = 0;
	while (true)
	{
			curLevel.PrintLevel();
		input = toupper(_getch());
		if (!(ProcessInput(&curLevel, &allLevels, input)))
			break;
		system("cls");
	}

	return 0;
}

void ChangePlayerPosition(levelInfo* curLevel, int x, int y)
{
	curLevel->mapArray[curLevel->playerCurIndex] = '.';
	curLevel->playerCurX = x;
	curLevel->playerCurY = y;
	curLevel->UpdatePlayerIndex();
	curLevel->mapArray[curLevel->playerCurIndex] = '@';
}

void UpdatePlayer(levelInfo* curLevel, std::vector<levelInfo>* allLevels, int x, int y)
{
	int index = curLevel->GetIndexAtCoordinates(x, y);

	switch (curLevel->mapArray[index])
	{
	case '.':
		ChangePlayerPosition(curLevel, x, y);
		break;
	case '#':
		break;
	case '|':
	case '-':
	case 'O':
		curLevel->ResetPlayer();
		break;
	case 'x':
		ResetLevel(curLevel);
		ChangeLevel(curLevel, allLevels, '+');
	}

}

void MovePlayer(levelInfo* curLevel, std::vector<levelInfo>* allLevels, char input)
{
	int tempX = curLevel->playerCurX;
	int tempY = curLevel->playerCurY;

	switch (input)
	{
	case 'W':
		--tempY;
		break;
	case 'S':
		++tempY;
		break;
	case 'A':
		--tempX;
		break;
	case 'D':
		++tempX;
		break;
	}
	UpdatePlayer(curLevel, allLevels, tempX, tempY);
}

void ChangeLevel(levelInfo* curLevel, std::vector<levelInfo>* allLevels, char input)
{
	int totalLevel = allLevels->size() - 1;
	int nextLevel = 0;
	switch (input)
	{
	case '+':
		nextLevel = curLevel->levelNumber + 1;
		if (nextLevel > totalLevel)
			nextLevel = 0;
		break;
	case '-':
		nextLevel = curLevel->levelNumber - 1;
		if (nextLevel < 0)
			nextLevel = totalLevel;
		break;
	default:
		return;
	}
	*curLevel = allLevels->at(nextLevel);
}

void ResetLevel(levelInfo* curLevel)
{
	//reset player position
	curLevel->ResetPlayer();

	//reset enemy locations
	// TODORO
}

bool ProcessInput(levelInfo* curLevel, std::vector<levelInfo>* allLevels, char input)
{
	enum inputs
	{
		moveUp = 'W',
		moveDown = 'S',
		moveLeft = 'A',
		moveRight = 'D',
		quit = 'X',
		reset = 'R',
		nextLevel = '=',
		prevLevel = '-',
	};
	switch (input)
	{
	case inputs::moveUp:
	case inputs::moveDown:
	case inputs::moveLeft:
	case inputs::moveRight:
		MovePlayer(curLevel, allLevels, input);
		break;
	case inputs::quit:
		return false;
	case inputs::reset:
		ResetLevel(curLevel);
		break;
	case inputs::nextLevel:
	case inputs::prevLevel:
		ChangeLevel(curLevel, allLevels, input);
	default:
		return true;
	}
	return true;
}
