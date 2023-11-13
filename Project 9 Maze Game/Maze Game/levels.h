#pragma once
struct location
{
	int m_xPos = 0;
	int m_yPos = 0;
	int m_index = 0;
};


class levelInfo
{
public:
	int playerStartX = 0;
	int playerStartY = 0;
	int playerCurX = 0;
	int playerCurY = 0;
	int playerCurIndex = 0;
	int arraySize = 0;
	int width = 0;
	int levelNumber = 0;
	char* mapArray = NULL;
	int* enemies = NULL;

public:
	void setCharacter();
	int GetXAtIndex(int index);
	int GetYAtIndex(int index);
	int GetIndexAtCoordinates(int x, int y);
	void UpdatePlayerIndex();
	void PrintLevel();
	void ResetPlayer();

};

std::vector<levelInfo> GetAllLevels();