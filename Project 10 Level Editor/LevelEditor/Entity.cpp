#include "level\LevelData.h"
#include "Entity.h"

#include <iostream>

void Entity::ResetLocation()
{
	m_currentLocation = m_startingLocation;
}

location Entity::GetCurrentLocation()
{
	return m_currentLocation;
}

void Entity::SetCurrentLocation(location newLocation)
{
	m_currentLocation = newLocation;
}

void Entity::SetCurrentLocation(int newX, int newY)
{
	m_currentLocation.x = newX;
	m_currentLocation.y = newY;
}

location Entity::GetStartingLocation()
{
	return m_startingLocation;
}

void Entity::SetStartingLocation(location newLocation)
{
	m_startingLocation = newLocation;
}

void Entity::SetStartingLocation(int newX, int newY)
{
	m_startingLocation.x = newX;
	m_startingLocation.y = newY;
}