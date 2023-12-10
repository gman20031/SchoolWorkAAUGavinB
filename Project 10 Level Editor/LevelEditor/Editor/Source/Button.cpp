#include <iostream>
#include <Windows.h>

#include "../Header/Button.h"
#include "../../Editor.h"
#include "../../Game.h"

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
