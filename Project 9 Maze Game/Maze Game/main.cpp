/* Summary of Game

Summary:
The user moves through a maze of walls to find an exit.

Game Specification:
    The user sees the maze in the form of a grid of tiles, with a size of at least 8 x 8.
    Use the '.' character to represent an empty tile.
    Use the '@' character to represent the player character's current position.
    Use the '#' character to represent a wall. The player cannot move through a wall.
    Use the 'X' character to represent the exit. When the player touches this, the game ends in a win.
	use the '-' and '|' character to represent enemy. Get sent to the beginning if the player touches the enemy.
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

void ChangePlayerPosition(levelInfo* pCurLevel, int x, int y);
void UpdatePlayer(levelInfo* pCurLevel, std::vector<levelInfo>* allLevels, int x, int y);
void MovePlayer(levelInfo* pCurLevel, std::vector<levelInfo>* allLevels, char input);
void ChangeLevel(levelInfo* pCurLevel, std::vector<levelInfo>* allLevels, char input);
void ResetLevel(levelInfo* pCurLevel);
void PrintIntro();
void PrintOutro();
bool ProcessInput(levelInfo* pCurLevel, std::vector<levelInfo>* allLevels, char input);
void MoveEnemies(levelInfo* pCurLevel);

int main()
{
	std::cout << "loading Level Info, if you see this, something is wrong or your computer is exceptionally slow" << std::endl;
	std::vector<levelInfo> allLevels = GetAllLevels();
	system("cls");

	char input = 0;
	levelInfo curLevel = allLevels.at(0); // start at level 1
	// the fact I made the levelData include a dyamic array here has very intersting implications, and why I need to reset the level- so read more there.

	PrintIntro();
	for (;;)
	{
		curLevel.PrintLevel();
		input = toupper(_getch());
		if (!(ProcessInput(&curLevel, &allLevels, input)))
			break;
		system("cls");
	}
	PrintOutro();


	return 0;
}

void PrintIntro()
{
	std::cout	<< "Hello, welcome to the Maze Game" << std::endl
				<< "You control the @ character, your goal is to get to the x on the map." << std::endl
				<< "Controls with WASD  -- x quits the game -- r resets the current level -- +/- will change levels" << std::endl
				<< "Have fun." << std::endl;
	system("pause");
	system("cls");
}

void PrintOutro()
{
	// I thought this would need more..
	std::cout << "thank you for playing" << std::endl;
}


void ChangePlayerPosition(levelInfo* pCurLevel, int x, int y)
{
	//----------------------------------------------------------------------------------
	// Takes the current level information and the x and y position you wish to move to
	// then switches the characters at the current players location and the location you wish to move to
	//----------------------------------------------------------------------------------

	if (pCurLevel->m_mapArray[pCurLevel->m_playerCurIndex] == '@') // I need to check this because the enemy characters will overwrite my player posistion before i move
		pCurLevel->m_mapArray[pCurLevel->m_playerCurIndex] = '.';
	pCurLevel->m_playerCurX = x;
	pCurLevel->m_playerCurY = y;
	pCurLevel->UpdatePlayerIndex();
	pCurLevel->m_mapArray[pCurLevel->m_playerCurIndex] = '@';
}

void UpdatePlayer(levelInfo* pCurLevel, std::vector<levelInfo>* allLevels, int x, int y)
{
	//----------------------------------------------------------------------------------
	// Takes the current level information, all usable Levels, and the x and y position you wish to move to
	// switches to the correct function depeneding on the character at that location
	//----------------------------------------------------------------------------------

	int index = pCurLevel->GetIndexAtCoordinates(x, y);

	MoveEnemies(pCurLevel);

	switch (pCurLevel->m_mapArray[index])
	{
	case '.':
		ChangePlayerPosition(pCurLevel, x, y);
		break;
	case '#':
		break;
	case '|':
	case '-':
	case 'O':
		pCurLevel->ResetPlayer();
		break;
	case 'x':
		ResetLevel(pCurLevel);
		ChangeLevel(pCurLevel, allLevels, '+');
	}
	if (pCurLevel->m_mapArray[pCurLevel->m_playerCurIndex] != '@')
		ResetLevel(pCurLevel);
}

void MoveEnemies(levelInfo* pCurLevel)
{
	//----------------------------------------------------------------------------------
	// For every enemy in the game
	// check if that enemy is going to walk into a wall
	// if not, move to that location
	// if it is, reverse the direction, then pause till next update.
	//----------------------------------------------------------------------------------

	for (int i = 0; i < pCurLevel->m_enemies.size(); ++i)
	{
		int nextIndex = pCurLevel->m_enemies.at(i).GetNextIndex(pCurLevel);
		char nextPosition = pCurLevel->m_mapArray[nextIndex];
		if (nextPosition == '.' or nextPosition == '@')
		{
			pCurLevel->m_enemies.at(i).StepEnemy(pCurLevel, nextIndex);
		}
		else
		{
			pCurLevel->m_enemies.at(i).TurnAround();
		}

	}
}

void MovePlayer(levelInfo* pCurLevel, std::vector<levelInfo>* allLevels, char input)
{
	//----------------------------------------------------------------------------------
	// Takes the current level, all levels, and the user input
	// Gets the X,Y coordinates of the tile the user wants to move to, then 
	// runs the function to check what is there, and performs the correct action
	// depending on what is at that square
	//----------------------------------------------------------------------------------

	int tempX = pCurLevel->m_playerCurX;
	int tempY = pCurLevel->m_playerCurY;

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
	UpdatePlayer(pCurLevel, allLevels, tempX, tempY);
}

void ChangeLevel(levelInfo* pCurLevel, std::vector<levelInfo>* allLevels, char input)
{
	//----------------------------------------------------------------------------------
	// Takes current level, all levels, and input character of + or - to increment or decrement the level.
	// Changes the variable currentLevel to be the next level meant to be played.
	//----------------------------------------------------------------------------------

	int totalLevel = allLevels->size() - 1;
	int nextLevel = 0;
	ResetLevel(pCurLevel);
	switch (input)
	{
	case '+':
		nextLevel = pCurLevel->m_levelNumber + 1;
		if (nextLevel > totalLevel)
			nextLevel = 0;
		break;
	case '-':
		nextLevel = pCurLevel->m_levelNumber - 1;
		if (nextLevel < 0)
			nextLevel = totalLevel;
		break;
	default:
		return;
	}
	*pCurLevel = allLevels->at(nextLevel);
}

void ResetLevel(levelInfo* pCurLevel)
{
	//--------------------------------------------------------------------------------------------------------------
	// This takes the current level and resets the entites to be
	// in their original locations..
	// 
	// This would not be neccary if the cString that contains the map was a static array
	// but since it is a pointer to the heap containing the memory, when I copy the level data from the vector
	// over to current level variable, the pointer is still pointing to the same place on the heap.
	// So every time i changed the position of anything, it would change it on the list of all levels as well, but
	// it wouldnt change the x,y or index values.
	// SO THATS why this is neccaray
	// 
	// basically, learn to have static arrays in classes, I dont know how tf that would work memory wise but /shrug
	//--------------------------------------------------------------------------------------------------------------

	//reset player position
	pCurLevel->ResetPlayer();

	//reset enemy locations
	for (int i = 0; i < pCurLevel->m_enemies.size(); ++i)
	{
		pCurLevel->m_enemies.at(i).ResetEnemy(pCurLevel);
	}
}

bool ProcessInput(levelInfo* pCurLevel, std::vector<levelInfo>* allLevels, char input)
{
	//------------------------------------------------------------------------------------------
	// Takes in current level, all levels, and user input
	// processes the input to do the correct outcome depending on what the user inputed
	//------------------------------------------------------------------------------------------

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
		MovePlayer(pCurLevel, allLevels, input);
		break;
	case inputs::quit:
		return false;
	case inputs::reset:
		ResetLevel(pCurLevel);
		break;
	case inputs::nextLevel:
		input = '+'; // ChangeLevel requires a + or - to increment or decrement level, and since pressing + on the keyboard returns = I change it to +
	case inputs::prevLevel:
		ChangeLevel(pCurLevel, allLevels, input);
		break;
	default:
		return true;
	}
	return true;
}
