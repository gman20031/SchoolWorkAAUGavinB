#pragma once

#include "../../LocationAndDirection.h"
#include "Entity.h"


class Enemy : Entity
{
	enum class direction
	{
		up = 0,
		right = 1,
		down = 2,
		left = 3,
	} static;
	int  m_currentDirection;
	char m_enemyType;

	void TurnAround();

public:
	enum class enemyType {
		horizontol = '-',
		verticle = '|',
	} static;

	Enemy(char type, Location start);

	Location GetNextLocation();
	void ResetEnemy();
	void StepEnemy(Location nextLocation);

};