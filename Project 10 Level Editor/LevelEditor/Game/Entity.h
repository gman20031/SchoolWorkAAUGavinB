#pragma once

#include "..\level\LevelData.h"

class Entity {

protected:
	location	m_currentLocation;
	location	m_startingLocation;
	levelInfo*	pThislevel;

public:
	void ResetLocation();

	const location GetCurrentLocation();
	void SetCurrentLocation(location newLocation);
	void SetCurrentLocation(int newX, int newY);

	const location GetStartingLocation();
	void SetStartingLocation(location newLocation);
	void SetStartingLocation(int newX, int newY);
};
