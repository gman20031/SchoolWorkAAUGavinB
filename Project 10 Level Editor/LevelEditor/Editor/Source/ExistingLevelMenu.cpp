#include "../Header/ExistingLevelMenu.h"

#include <filesystem>
#include <string>
#include <iostream>
#include <conio.h>
#include <algorithm>

#include "../../Editor.h"
#include "../../Game.h"


LevelMenuButton::LevelMenuButton(const std::filesystem::path* filePath)
{
	m_filePath = *filePath;
	m_displayText = m_filePath.filename().string();
	m_isSelected = false;
}

void LevelMenuButton::EventHandler() const
{
	LevelEditMenu editMenu(&m_filePath);

	while (editMenu.m_keepEditing)
	{
		system("cls");
		editMenu.PrintEditMenu();
		char input = _getch();
		if (input == 'e')
			editMenu.HandleInteraction();
		else if (input == Inputs::kSpecialWindowKey)
		{
			Direction dir = Inputs::GetDirFromArrowKey();
			editMenu.MoveCursor(dir);
		}
	}
}

LevelMenuButton* ExistingLevelMenu::GetButtonAt(int yIndex)
{
	return &m_buttonGrid.at(yIndex);
}


/////////////////////////////////////////////////////////
///////// Level Menu
/////////////////////////////////////////////////////////

void ExistingLevelMenu::SetCursorLocation(Location target)
{
	if (GetButtonAt(m_targetButtonLocation)->m_isSelected)
		GetButtonAt(m_targetButtonLocation)->m_isSelected = false;
	m_targetButtonLocation = target;
	GetButtonAt(target)->m_isSelected = true;
}

void ExistingLevelMenu::EnsureInBounds()
{
	m_targetButtonLocation.x = 0;
	m_targetButtonLocation.y = std::clamp(m_targetButtonLocation.y, 0, (int)m_buttonGrid.size() - 1);
}

void ExistingLevelMenu::MoveCursor(Direction direction)
{
	GetButtonAt(m_targetButtonLocation)->m_isSelected = false;
	Inputs::MoveLocation(&m_targetButtonLocation, direction);
	EnsureInBounds();
	GetButtonAt(m_targetButtonLocation)->m_isSelected = true;
}

LevelMenuButton* ExistingLevelMenu::GetButtonAt(Location target)
{
	return &m_buttonGrid.at(m_targetButtonLocation.y);
}

void ExistingLevelMenu::DisplayAllText() const
{
	std::cout << m_menuTitle << std::endl;
	for (auto& currentButton : m_buttonGrid)
	{
		if (currentButton.m_isSelected)
			currentButton.DisplayTextselected();
		else
			currentButton.DisplayText();
		std::cout << '\n';
	}
}

void ExistingLevelMenu::AddButtonNewLine(const std::filesystem::path* newPath)
{
	LevelMenuButton B_TempButton(newPath);
	m_buttonGrid.emplace_back(B_TempButton);
}
void ExistingLevelMenu::PressSelectedButton()
{
	GetButtonAt(m_targetButtonLocation.y)->EventHandler();
}