#include <iostream>
#include <Windows.h>

#include "Menu.h"

//////////////////////////////////////////
// Button Stuff
//////////////////////////////////////////

Button::Button(std::string name) : m_displayText(name)
{
		
}

const void Button::DisplayText()
{
	std::cout << m_displayText;
}

const void Button::DispalyTextselected()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, Menu::kSelectedColor);
	std::cout << m_displayText;
	SetConsoleTextAttribute(consoleHandle, Menu::kStandarColor);
}

//////////////////////////////////////////
// Menu Stuff
//////////////////////////////////////////

const void Menu::DisplayText()
{
	std::cout << m_menuTitle << std::endl;
}

const void Menu::AddButton(Button* newButton)
{
	m_allButtons.emplace_back(newButton);
}

const void Menu::InsertButton(int yPos, Button* newButton)
{
	m_allButtons.emplace(m_allButtons.begin()+yPos, newButton);
}

const int Menu::GetMenuLength()
{
	return m_allButtons.size();
}
