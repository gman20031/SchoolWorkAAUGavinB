#pragma once

#include <string>
#include "../../LocationAndDirection.h"

class Inputs
{
public:
	static Direction GetDirFromArrowKey();
	static constexpr int kSpecialWindowKey = -32;
	static void HandleArrowKey(Location* Location);
	static void MoveLocation(Location* Location, Direction dir);
	static int GetMeAnInt();
	static bool SetStringFromUser(std::string& str);
};