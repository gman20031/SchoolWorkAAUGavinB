#pragma once

#include "level\LevelData.h"

class Entity {
	location m_currentLocation;
	location m_startingLocation;

public:
	void ResetLocation();

	location GetCurrentLocation();
	void SetCurrentLocation(location newLocation);
	void SetCurrentLocation(int newX, int newY);

	location GetStartingLocation();
	void SetStartingLocation(location newLocation);
	void SetStartingLocation(int newX, int newY);
};
