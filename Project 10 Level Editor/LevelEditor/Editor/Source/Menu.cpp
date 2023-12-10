#include <iostream>
#include <Windows.h>
#include <algorithm>

#include "../Header/Menu.h"
#include "../../Editor.h"
#include "../../Game.h"

//////////////////////////////////////////
// Button Stuff
//////////////////////////////////////////

MenuButton::MenuButton(const char* name, std::function<void(std::vector<Menu*>*)> eventFunction)
	: m_eventFunction(eventFunction)
{
	m_isSelected = false;
	m_displayText = name;
}

void MenuButton::EventHandler(std::vector<Menu*>* MenuStack) const
{
	m_eventFunction(MenuStack);
}

//////////////////////////////////////////
// Menu Stuff
//////////////////////////////////////////

Menu::Menu(const char* title, Menu* rootMenu) : m_rootMenu(rootMenu)
{
	if(rootMenu != nullptr)
		rootMenu->AddSubMenu(this);
	m_menuTitle = title;
	m_targetButtonLocation = { 0,0 };
}

MenuButton* Menu::GetButtonAt(Location target)
{
	return m_buttonGrid.at(m_targetButtonLocation.y).at(m_targetButtonLocation.x);
}

void Menu::AddSubMenu(Menu* newSubMenu)
{
	m_subMenus.push_back(newSubMenu);
}

//Menu* Menu::GetRootMenu()
//{
//	return m_rootMenu;
//}

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
		}
		std::cout << '\n';
	}
}

 void Menu::AddButtonNewLine(MenuButton* newButton)
{
	 m_buttonGrid.emplace_back();
	 m_buttonGrid.back().push_back(newButton);
}

 void Menu::InsertButton(int xPos, int yPos, MenuButton* newButton)
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

 void Menu::SetCursorLocation(Location newLocation)
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
	Inputs::MoveLocation(&m_targetButtonLocation, direction);
	EnsureInBounds();
	GetButtonAt(m_targetButtonLocation)->m_isSelected = true;
 }

 Location* Menu::GetTargetLocation()
 {
	 return &m_targetButtonLocation;
 }


 void Menu::PressSelectedButton(std::vector<Menu*>* menuStack)
 {
	 GetButtonAt(m_targetButtonLocation)->EventHandler(menuStack);
 }

