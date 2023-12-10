#pragma once

#include "../../LocationAndDirection.h"
#include "LevelData.h"

class Entity {

protected:
	Location	m_currentLocation;
	Location	m_startingLocation;
	levelInfo*	pThislevel;

public:
	void ResetLocation();

	const Location GetCurrentLocation();
	void SetCurrentLocation(Location newLocation);
	void SetCurrentLocation(int newX, int newY);

	const Location GetStartingLocation();
	void SetStartingLocation(Location newLocation);
	void SetStartingLocation(int newX, int newY);
};
