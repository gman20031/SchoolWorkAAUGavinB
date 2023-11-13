#include <iostream>
#include <vector>
#include <fstream> // for filereading
#include <conio.h> // _getch()
#include <string> // strings
#include "levels.h" // structs and getting level info from file



void levelInfo::setCharacter() {
	if (arraySize < 1) // cant run if struct not filled properly
	{
		std::cout << ("levelInfo Not valid") << std::endl;
		return;
	}
	mapArray[playerCurIndex] = '@';

}

int levelInfo::GetXAtIndex(int index)
{
	return index % width;
}

int levelInfo::GetYAtIndex(int index)
{
	return index / width;
}

int levelInfo::GetIndexAtCoordinates(int x, int y)
{
	return x + y * width;
}

void levelInfo::UpdatePlayerIndex()
{
	playerCurIndex = GetIndexAtCoordinates(playerCurX, playerCurY);
}

void levelInfo::PrintLevel()
{
	for (int i = 0; i < arraySize; ++i) // Make this faster???? idk, only better way to do this is to like, learn to unwrite stuff written, or using actual graphics library
	{
		std::cout << mapArray[i] << ' ';
		if (((i + 1) % (width)) == 0)
			std::cout << std::endl;
	}

}

void levelInfo::ResetPlayer()
{
	//reset player position
	mapArray[playerCurIndex] = '.';
	playerCurX = playerStartX;
	playerCurY = playerStartY;
	UpdatePlayerIndex();
	mapArray[playerCurIndex] = '@';
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

void FillLevelInformation(levelInfo* currLevel, std::string* currMap, int currentIteration)
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
*/
	// Get width -- lil cheat, but is the easiest solution I can think of right now
	currLevel->width = currMap->at(currMap->size() - 1);
	currMap->pop_back();

	// Get array size
	currLevel->arraySize = currMap->size();

	// Get player current index.
	currLevel->playerCurIndex = currMap->find_first_of('@', currLevel->width); // I find the first occurance of @ starting at width since I know it will not be on the first line as it is ALWAYS a line of #

	// Get start and current X and Y's for the player
	int tempX, tempY;
	tempX = currLevel->GetXAtIndex(currLevel->playerCurIndex);
	tempY = currLevel->GetYAtIndex(currLevel->playerCurIndex);
	currLevel->playerCurX = tempX;
	currLevel->playerStartX = tempX;
	currLevel->playerCurY = tempY;
	currLevel->playerStartY = tempY;

	// Sets the level number
	currLevel->levelNumber = currentIteration;

	// Allocate MapArray and convert string to c string to then allocate.
	currLevel->mapArray = new char[currMap->size()];
	ConvertToCString(currLevel->mapArray , currMap);;

	// Get Enemy start locations
	for (int i = 0, tempIndex = 0; i >= 0; i = currMap->find_first_of('-', tempIndex))
	{

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

