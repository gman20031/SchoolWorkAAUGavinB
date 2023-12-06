#pragma once

#include "Level/LevelData.h"
#include "Menu.h"

class WallSelector : public Button
{

public:
	using Button::Button;

};

class EnemyHorizontalSelector : Button 
{

public:
	using Button::Button;
};

class EnemyVerticleSelector : Button
{

public:
	using Button::Button;
};

class TrapSelector : Button
{

public:
	using Button::Button;
};

class LevelEditMenu : public Menu
{
	levelInfo* m_pCurrentLevel;
	std::vector
public:

};
