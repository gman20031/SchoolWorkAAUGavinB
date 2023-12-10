#pragma once

#include <filesystem>
#include <string>
#include <iostream>
#include <conio.h>

#include "LevelEditMenu.h"
#include "Menu.h"
#include "Button.h"

class LevelMenuButton : public Button
{
	mutable std::filesystem::path m_filePath; //wtf I thought mutable what implicity, now I need to specify


public:

	LevelMenuButton(const std::filesystem::path* filePath);

	void EventHandler() const;
};

class ExistingLevelMenu : public Menu
{
	std::vector<LevelMenuButton> m_buttonGrid;
	LevelMenuButton* GetButtonAt(Location target);
	void EnsureInBounds();

public:
	Menu::Menu;

	LevelMenuButton* GetButtonAt(int yIndex);

	void MoveCursor(Direction direction);
	void SetCursorLocation(Location target);
	void DisplayAllText() const;
	void AddButtonNewLine(const std::filesystem::path* newPath);
	void PressSelectedButton();
};
