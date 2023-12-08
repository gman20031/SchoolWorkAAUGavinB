#include <iostream>
#include <Windows.h>
#include <algorithm>

#include "Menu.h"

//////////////////////////////////////////
// Button Stuff
//////////////////////////////////////////

Button::Button(const char* name, std::function<void(Menu*)> eventFunction)
	: m_eventFunction(eventFunction)
{
	m_isSelected = false;
	m_displayText = name;
}

void Button::DisplayText() const
{
	std::cout << m_displayText;
}

void Button::DisplayTextselected() const
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, Menu::kRedColor);
	std::cout << m_displayText;
	SetConsoleTextAttribute(consoleHandle, Menu::kStandarColor);
}

void Button::EventHandler(Menu* currentMenu) const
{
	m_eventFunction(currentMenu);
}

//////////////////////////////////////////
// Menu Stuff
//////////////////////////////////////////

Button* Menu::GetButtonAt(location target)
{
	return m_buttonGrid.at(m_targetButtonLocation.y).at(m_targetButtonLocation.x);
}

Menu::Menu(const char* title, Menu* rootMenu) : m_rootMenu(rootMenu)
{
	m_menuTitle = title;
	m_targetButtonLocation = { 0,0 };
}

void Menu::AddSubMenu(Menu* newSubMenu)
{
	m_subMenus.push_back(newSubMenu);
}

Menu* Menu::GetRootMenu()
{
	return m_rootMenu;
}

Menu* Menu::GetSubMenu(int index)
{
	return m_subMenus.at(index);
}

 void Menu::DisplayAllText() const
{
	std::cout << m_menuTitle << std::endl;
	for (auto &currentRow : m_buttonGrid)
	{
		for (auto currentButton : currentRow)
		{
			if (currentButton->m_isSelected)
				currentButton->DisplayTextselected();
			else
				currentButton->DisplayText();
			std::cout << " | ";
		}
		std::cout << '\n';
	}
}

 void Menu::AddButtonNewLine(Button* newButton)
{
	 m_buttonGrid.emplace_back();
	 m_buttonGrid.back().push_back(newButton);
}

 void Menu::InsertButton(int xPos, int yPos, Button* newButton)
{
	 auto index = m_buttonGrid.at(yPos).begin() + xPos;
	 m_buttonGrid.at(yPos).insert(index, newButton);
}

 size_t Menu::GetMenuLength() const
{
	return m_buttonGrid.size();
}

 size_t Menu::GetLegthAtY(int yPos) const
 {
	return m_buttonGrid.at(yPos).size();
 }

 void Menu::SetCursorLocation(location newLocation)
 {
	 if(GetButtonAt(m_targetButtonLocation)->m_isSelected)
		 GetButtonAt(m_targetButtonLocation)->m_isSelected = false;
	 m_targetButtonLocation = newLocation;
	 GetButtonAt(newLocation)->m_isSelected = true;
 }

 void Menu::EnsureInBounds()
 {
	 m_targetButtonLocation.y = std::clamp(m_targetButtonLocation.y, 0, (int)GetMenuLength()-1);
	 m_targetButtonLocation.x = std::clamp(m_targetButtonLocation.x, 0, (int)GetLegthAtY(m_targetButtonLocation.y)-1 );
 }

 void Menu::MoveCursor(Direction direction)
 {
	 GetButtonAt(m_targetButtonLocation)->m_isSelected = false;
	 switch (direction)
	 {
	 case Direction::kDown:
		 ++m_targetButtonLocation.y; break;
	 case Direction::kUp:
		 --m_targetButtonLocation.y; break;
	 case Direction::kLeft:
		 --m_targetButtonLocation.x; break;
	 case Direction::kRight:
		 ++m_targetButtonLocation.x; break;
	 }
	 EnsureInBounds();
	 GetButtonAt(m_targetButtonLocation)->m_isSelected = true;
 }



 void Menu::PressSelectedButton(Menu* currentMenu)
 {
	 GetButtonAt(m_targetButtonLocation)->EventHandler(currentMenu);
 }