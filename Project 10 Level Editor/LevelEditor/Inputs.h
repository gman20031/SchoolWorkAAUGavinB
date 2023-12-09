#pragma once

#include "LocationAndDirection.h"

class Inputs
{
public:
	static void HandleArrowKey(Location* Location);
	static void MoveLocation(Location* Location, Direction dir);
	static int GetMeAnInt();
};