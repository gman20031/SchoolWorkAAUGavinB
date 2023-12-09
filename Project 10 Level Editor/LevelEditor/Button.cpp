#include <iostream>
#include <Windows.h>

#include "Button.h"
#include "Menu.h"

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
