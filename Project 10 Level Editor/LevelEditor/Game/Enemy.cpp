#include <assert.h>

#include "..\level\LevelData.h"
#include "Entity.h"
#include "Enemy.h"

Enemy::Enemy(char type, location start)
{
	assert(type == (char)enemyType::horizontol or type == (char)enemyType::verticle);
	m_startingLocation = start;
	m_currentLocation = start;

	switch(type)
	{
	case (char)enemyType::horizontol:
		m_enemyType = (char)enemyType::horizontol;
		m_currentDirection = (int)direction::right;
		break;
	case (char)enemyType::verticle:
		m_enemyType = (char)enemyType::verticle;
		m_currentDirection = (int)direction::down;
	}

}

location Enemy::GetNextLocation()
{
	location nextLocation = m_currentLocation;
	switch (m_currentDirection)
	{
	case (int)direction::up:
		nextLocation.y -= 1;
		break;
	case (int)direction::down:		
		nextLocation.y += 1;
		break;
	case (int)direction::right:
		nextLocation.x += 1;
		break;
	case (int)direction::left:
		nextLocation.x -= 1;
		break;
	}
	return nextLocation;
}

void Enemy::TurnAround()
{
	switch (m_currentDirection)
	{
	case (int)direction::up:
		m_currentDirection = (int)direction::down;
		break;
	case (int)direction::down:
		m_currentDirection = (int)direction::up;
		break;
	case (int)direction::right:
		m_currentDirection = (int)direction::left;
		break;
	case (int)direction::left:
		m_currentDirection = (int)direction::right;
		break;
	}
}

void Enemy::ResetEnemy()
{
	ResetLocation();
	switch (m_enemyType)
	{
	case (char)enemyType::horizontol:
		m_currentDirection = (int)direction::right;
		break;
	case (char)enemyType::verticle:
		m_currentDirection = (int)direction::down;
	}
}

void Enemy::StepEnemy(location nextLocation)
{
	if (pThislevel->GetAt(nextLocation) == levelInfo::kEmptySpaceChar)
	{
		pThislevel->SetAt(m_currentLocation, levelInfo::kEmptySpaceChar);
		SetCurrentLocation(nextLocation);
		pThislevel->SetAt(nextLocation, m_enemyType);
	}
	else
	{
		TurnAround();
	}
}
		
