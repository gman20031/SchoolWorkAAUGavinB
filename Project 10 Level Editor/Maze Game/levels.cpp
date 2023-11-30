#include <iostream>
#include <vector>
#include <fstream> // for filereading
#include <string> // strings
#include "levels.h" // structs and getting level info from file


int levelInfo::GetXAtIndex(int index)
{
	return index % m_width;
}

int levelInfo::GetYAtIndex(int index)
{
	return index / m_width;
}

int levelInfo::GetIndexAtCoordinates(int x, int y)
{
	return x + y * m_width;
}

void levelInfo::UpdatePlayerIndex()
{
	m_playerCurIndex = GetIndexAtCoordinates(m_playerCurX, m_playerCurY);
}

void levelInfo::PrintLevel()
{
	//Prints out the current cString that is the map
	for (int i = 0; i < m_arraySize; ++i) // Make this faster???? idk, only better way to do this is to like, learn to unwrite stuff written, or using actual graphics library
	{
		std::cout << m_mapArray[i] << ' ';
		if (((i + 1) % (m_width)) == 0) // unsure how modulo works, but is probably still pretty fast if using bitwise math.
			std::cout << std::endl;
	}
}

void levelInfo::ResetPlayer()
{
	//reset player position to where it started when the map was loaded in
	m_mapArray[m_playerCurIndex] = '.';
	m_playerCurX = m_playerStartX;
	m_playerCurY = m_playerStartY;
	UpdatePlayerIndex();
	m_mapArray[m_playerCurIndex] = '@';
}

void levelInfo::AddEnemy(char type, int index)
{
	/*
		fills out info of enemy class
		m_startLoc;
		m_currentLoc;	
		m_currentDirection
		m_enemyType;
		then adds it to the vector containing all enemies
	*/
	enemy tempEnemy;
	tempEnemy.SetType(type);
	tempEnemy.FillLocations(index, GetXAtIndex(index), GetYAtIndex(index));
	m_enemies.push_back(tempEnemy);
}

void enemy::FillLocations(int index, int x, int y)
{
	// Takes the x,y, and index values of the enemy and fills sets the current and starting location structs to those values
	m_startLoc.index = index;
	m_startLoc.xPos = x;
	m_startLoc.yPos = y;
	m_currentLoc = m_startLoc;
}

void enemy::SetType(char type) {
	// sets the enemy type to the value specified by the argument.
	m_enemyType = type;
	switch (m_enemyType)
	{
	case enemyTypes::horizontal:
		m_currentDirection = directions::right;
		break;
	case enemyTypes::verticle:
		m_currentDirection = directions::up;
	}
}

int enemy::GetNextIndex(levelInfo *currLevel)
{	
	// Takes the current level, and finds the index of where the current enemy is supposed to move to.
	// this is the same code i used to get the player information........... hmmmmmmm? except i use directions:: instead of wasd.. another reason to impliment a greater entity class and inherit instead.
	int tempX = m_currentLoc.xPos;
	int tempY = m_currentLoc.yPos;
	switch (m_currentDirection)
	{
	case directions::up:
		--tempY;
		break;
	case directions::down:
		++tempY;
		break;
	case directions::left:
		--tempX;
		break;
	case directions::right:
		++tempX;
		break;
	}
	return (currLevel->GetIndexAtCoordinates(tempX, tempY));
}

void enemy::StepEnemy(levelInfo *currLevel, int nextIndex)
{
	// Moves the enemy's current location to the index provided
	// sets the current location in the map array to . and sets the new location to this enemies type.
	currLevel->m_mapArray[m_currentLoc.index] = '.';
	m_currentLoc.index = nextIndex;
	m_currentLoc.xPos = currLevel->GetXAtIndex(nextIndex);
	m_currentLoc.yPos = currLevel->GetYAtIndex(nextIndex);
	currLevel->m_mapArray[m_currentLoc.index] = m_enemyType;
}

void enemy::TurnAround() {
	//Switches the direction the enemy is facing, if left goes right and vice versa, and the same for up and down.

	switch (m_enemyType)
	{
	case enemyTypes::horizontal:
		if (m_currentDirection == directions::left)
			m_currentDirection = directions::right;
		else
			m_currentDirection = directions::left;
		break;
	case enemyTypes::verticle:
		if (m_currentDirection == directions::up)
			m_currentDirection = directions::down;
		else
			m_currentDirection = directions::up;
	}

}

void enemy::ResetEnemy(levelInfo* currLevel)
{
	// Resets the enemies location and position on the map array to the same as when loaded from the txt
	currLevel->m_mapArray[m_currentLoc.index] = '.';
	m_currentLoc = m_startLoc;
	currLevel->m_mapArray[m_currentLoc.index] = m_enemyType;
}

void ReadInFile(std::vector<std::string>* maps)
{
	// Reads in the Maps.txt file cuts each map up based on where it encounters a '0'
	// then adds that std::string to the vector containing all maps.
	// if a end of file is reached before a 0 it will ignore it, though this is being buggy so beware adding to the .txt after the last 0
	std::fstream myfile;
	myfile.open("Maps.txt");
	if (myfile.is_open())
	{
		std::string tempString = "0";

		while (getline(myfile, tempString, '0'))
		{
			if (myfile.eof())
				break;
			maps->push_back(tempString);
		}

		myfile.close();
	}
	else
	{
		std::cout << "your -redacted- trash lol ";
	}
}

void CleanStrings(std::vector<std::string>* allStrings)
{
	// Takes a vector containt std::strings
	// Removes all instances of a endline, space, and tab from every string.
	// adds the width of the map to the end of the string, width based on the where the first endline is found
	// only does the above as long as there were characters found, and not already found a width.
	// this is in an attempt to stop start reading a string AT the endline, and thinking the width is zero, thus causing a divide by zero error in the future.
	// This does not allow for making bad maps in the Txt file.
	constexpr char  kendL = '\n',
				kspace = ' ',
				ktab = '\t';

	for (int i = 0; i < allStrings->size(); ++i) // iterates through every string
	{
		int width = 0;
		int counter = 0;
		for (std::string::iterator myIt = allStrings->at(i).begin(); myIt != allStrings->at(i).end();) // iterates through every character in that string
		{
			switch (*myIt) {
			case ktab:
			case kspace:
				allStrings->at(i).erase(myIt); // if any character is one of the above, remove it.
				break;
			case kendL:
				if (width == 0 and counter != 0)
					width = counter;
				allStrings->at(i).erase(myIt);
				break;
			default:		// .erase automatically removes the index that it points at, so I only need to iterate if I DONT erase. 
				++myIt;		//(i.e, if the second character is a space, if I remove it the second charcter will not be what was on the next element
				++counter;
			}//switchClose
		}
		allStrings->at(i).shrink_to_fit();
		allStrings->at(i).push_back(width);
	}
}

std::vector<std::string> GetMapStrings()
{
	// Reads in the Maps.TXT
	// Cleans the maps to remove things like spaces(see cleanStrings function)
	// organizes all of the maps into a vector and returns that vector

	std::vector<std::string> allStrings;

	ReadInFile(&allStrings);
	if (allStrings.size() <= 0)
	{
		std::cout << "error reading maps" << std::endl;
		return allStrings;
	}
	CleanStrings(&allStrings);
	return allStrings;
}

void ConvertToCString(char* cString, std::string* stdString)
{
	// assumed to be same length, since this is my damn program I know it will be.
	for (int i = 0; i < stdString->size(); ++i)
	{
		cString[i] = stdString->at(i);
	}
	cString[stdString->size() + 1] = '\0';
}

void FillLevelInformation(levelInfo* pCurrLevel, std::string* pCurrMap, int currentIteration)
{
	/* fills this information -- if information does not match class, will not fill that information
		int playerStartX = 0;
		int playerStartY = 0;
		int playerCurX = 0;
		int playerCurY = 0;
		int playerCurIndex = 0;
		int arraySize = 0;
		int width = 0;
		int levelNumber = 0;
		char* mapArray;
		std::vector<enemy> m_enemies;
	*/

	// Get width -- lil cheat, but is the easiest solution I can think of right now
	pCurrLevel->m_width = pCurrMap->at(pCurrMap->size() - 1);
	pCurrMap->pop_back();

	// Get array size
	pCurrLevel->m_arraySize = pCurrMap->size();

	// Get player current index.
	pCurrLevel->m_playerCurIndex = pCurrMap->find_first_of('@', pCurrLevel->m_width); // I find the first occurance of @ starting at width since I know it will not be on the first line as it is ALWAYS a line of #

	// Get start and current X and Y's for the player
	int tempX, tempY;
	tempX = pCurrLevel->GetXAtIndex(pCurrLevel->m_playerCurIndex);
	tempY = pCurrLevel->GetYAtIndex(pCurrLevel->m_playerCurIndex);
	pCurrLevel->m_playerCurX = tempX;
	pCurrLevel->m_playerStartX = tempX;
	pCurrLevel->m_playerCurY = tempY;
	pCurrLevel->m_playerStartY = tempY;

	// Sets the level number
	pCurrLevel->m_levelNumber = currentIteration;

	// Allocate MapArray and convert string to c string to then allocate.
	pCurrLevel->m_mapArray = new char[pCurrMap->size()+1];//+1 to add \0
	ConvertToCString(pCurrLevel->m_mapArray, pCurrMap);;

	// Get Enemy start locations
	for (int i = 0; i < pCurrMap->size(); ++i)
	{
		switch (pCurrMap->at(i))
		{
		case '|':
		case '-':
			pCurrLevel->AddEnemy(pCurrMap->at(i), i);
		}
	}
}

std::vector<levelInfo> GetAllLevels()
{
	//wording help, for me more than you
	// level = the idea of every piece of info needed to make a level
	// map = the array that makes up what people look at.

	// Gets all the map arrays from the maps.txt As std::strings
	// then fills out all the informaion within the levelInfo class based on the maps imported
	// and converts them to cStrings

	std::vector<std::string> allMaps = GetMapStrings(); // get all maps 
	std::vector<levelInfo> levelOutput(allMaps.size());
	for (int i = 0; i < levelOutput.size(); ++i)
		FillLevelInformation(&levelOutput.at(i), &allMaps.at(i), i);
	return levelOutput;
}

