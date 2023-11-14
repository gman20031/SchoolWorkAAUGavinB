#include <iostream>
#include <vector>
#include <fstream> // for filereading
#include <string> // strings
#include "levels.h" // structs and getting level info from file



void levelInfo::setCharacter() {
	if (m_arraySize < 1) // cant run if struct not filled properly
	{
		std::cout << ("levelInfo Not valid") << std::endl;
		return;
	}
	m_mapArray[m_playerCurIndex] = '@';

}

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
	for (int i = 0; i < m_arraySize; ++i) // Make this faster???? idk, only better way to do this is to like, learn to unwrite stuff written, or using actual graphics library
	{
		std::cout << m_mapArray[i] << ' ';
		if (((i + 1) % (m_width)) == 0)
			std::cout << std::endl;
	}
}

void levelInfo::ResetPlayer()
{
	//reset player position
	m_mapArray[m_playerCurIndex] = '.';
	m_playerCurX = m_playerStartX;
	m_playerCurY = m_playerStartY;
	UpdatePlayerIndex();
	m_mapArray[m_playerCurIndex] = '@';
}

void levelInfo::AddEnemy(char type, int index)
{
	/*
		fills out info
		m_startLoc;
		m_currentLoc;	
		m_currentDirection
		m_enemyType;
	*/
	enemy tempEnemy;
	tempEnemy.SetType(type);
	tempEnemy.FillLocations(index, GetXAtIndex(index), GetYAtIndex(index));
	m_enemies.push_back(tempEnemy);
}

void enemy::FillLocations(int index, int x, int y)
{
	m_startLoc.index = index;
	m_startLoc.xPos = x;
	m_startLoc.yPos = y;
	m_currentLoc = m_startLoc;
}

void enemy::SetType(char type) {
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
{	// this is the same code i used to get the player information........... hmmmmmmm
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
	currLevel->m_mapArray[m_currentLoc.index] = '.';
	m_currentLoc.index = nextIndex;
	m_currentLoc.xPos = currLevel->GetXAtIndex(nextIndex);
	m_currentLoc.yPos = currLevel->GetYAtIndex(nextIndex);
	currLevel->m_mapArray[m_currentLoc.index] = m_enemyType;
}

void enemy::TurnAround() {
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
	currLevel->m_mapArray[m_currentLoc.index] = '.';
	m_currentLoc = m_startLoc;
	currLevel->m_mapArray[m_currentLoc.index] = m_enemyType;
}

void ReadInFile(std::vector<std::string>* maps)
{
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
}

void FillLevelInformation(levelInfo* pCurrLevel, std::string* pCurrMap, int currentIteration)
{
	/* fills this information -- if information does not match struct, will not fill that information
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
	pCurrLevel->m_mapArray = new char[pCurrMap->size()];
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
	std::vector<std::string> allMaps = GetMapStrings(); // get all maps 
	std::vector<levelInfo> levelOutput(allMaps.size());
	for (int i = 0; i < levelOutput.size(); ++i)
		FillLevelInformation(&levelOutput.at(i), &allMaps.at(i), i);
	return levelOutput;
}

