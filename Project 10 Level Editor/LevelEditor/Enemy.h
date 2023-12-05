#pragma once
#include "level\LevelData.h"
#include "Entity.h"

class Enemy : Entity
{
	enum class enemyType {
		horizontol = '-',
		verticle = '|',
	};
	enum class direction
	{
		up = 0,
		right = 1,
		down = 2,
		left = 3,
	};
	direction m_currentDirection;
	enemyType m_enemyType;

public:
	void SetType(char type);
	void TurnAround();
	void ResetEnemy(levelInfo* currLevel);
	void StepEnemy(levelInfo* currLevel, location nextLocation);

};