#pragma once

// I was told I should most likely split every object into their own header files. Sounds reasonable, but did not want to implement in this project

class enemy;
class levelInfo;

struct location
{
	int xPos = 0;
	int yPos = 0;
	int index = 0;
};

class enemy
{
	location m_startLoc;
	location m_currentLoc;
	enum directions
	{
		up = 0,
		right = 1,
		down = 2,
		left = 3,
	};
	unsigned int m_currentDirection = directions::up;
	enum enemyTypes
	{
		horizontal = '-',
		verticle = '|',
	};
	char m_enemyType = 0;

public:
	void FillLocations(int index, int x, int y);
	void SetType(char type);
	void TurnAround();
	void ResetEnemy(levelInfo* currLevel);
	void StepEnemy(levelInfo *currLevel, int nextIndex);
	int GetNextIndex(levelInfo *currLevel);
};

class levelInfo
{
	/*
		This class contains all the information of the level
		The information of level includes
			the map array containng the characters that are the map being displayer
			The width of the level
			the number that level is
			Every enemy within that level.
			The player within that level.
	*/
public:
	int m_playerStartX = 0;
	int m_playerStartY = 0;
	int m_playerCurX = 0;
	int m_playerCurY = 0;
	int m_playerCurIndex = 0;
	int m_arraySize = 0;
	int m_width = 0;
	int m_levelNumber = 0;
	char* m_mapArray = nullptr; // this being a normal cstring caused many complications and annoyances
	std::vector<enemy> m_enemies;

	~levelInfo() { delete m_mapArray; } // now this should let me not worry about memory deletion myself?

	int GetXAtIndex(int index);
	int GetYAtIndex(int index);
	int GetIndexAtCoordinates(int x, int y);
	void UpdatePlayerIndex();
	void PrintLevel();
	void ResetPlayer();
	void AddEnemy(char type, int index);
};

std::vector<levelInfo> GetAllLevels();