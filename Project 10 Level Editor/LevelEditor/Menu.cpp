#include <iostream>
#include <Windows.h>

#include "Menu.h"

//////////////////////////////////////////
// Button Stuff
//////////////////////////////////////////

Button::Button(std::string name , std::function<void()> eventFunction)
	: m_displayText(name)
	, m_eventFunction(eventFunction)
{}

void Button::DisplayText() const
{
	std::cout << m_displayText;
}

void Button::DispalyTextselected() const
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, Menu::kSelectedColor);
	std::cout << m_displayText;
	SetConsoleTextAttribute(consoleHandle, Menu::kStandarColor);
}

void Button::EventHandler() const
{
	m_eventFunction();
}

//////////////////////////////////////////
// Menu Stuff
//////////////////////////////////////////

 void Menu::DisplayText() const
{
	std::cout << m_menuTitle << std::endl;
}

 void Menu::AddButton(Button* newButton) 
{
	m_allButtons.emplace_back(newButton);
}

 void Menu::InsertButton(int index, Button* newButton)  
{
	m_allButtons.emplace(m_allButtons.begin()+index, newButton);
}

 size_t Menu::GetMenuLength() const
{
	return m_allButtons.size();
}
