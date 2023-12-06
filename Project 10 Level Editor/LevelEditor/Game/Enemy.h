#pragma once

#include "..\level\LevelData.h"
#include "Entity.h"

class Enemy : Entity
{
	static enum class direction
	{
		up = 0,
		right = 1,
		down = 2,
		left = 3,
	};
	int  m_currentDirection;
	char m_enemyType;

	void TurnAround();

public:
	static enum class enemyType {
		horizontol = '-',
		verticle = '|',
	};

	Enemy(char type, location start);

	location GetNextLocation();
	void ResetEnemy();
	void StepEnemy(location nextLocation);

};