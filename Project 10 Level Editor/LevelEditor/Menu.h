#pragma once
#include <string>

#include "Level/levelData.h"
class Menu;

class Button
{
protected:
	std::string m_displayText;
	Menu* m_containerMenu;

public:
	Button(std::string name);

	const void DisplayText();
	const void DispalyTextselected();
};

class Menu
{
protected:
	std::string m_menuTitle;
	std::vector<Button*> m_allButtons;

public:
	static constexpr int kSelectedColor = 4;
	static constexpr int kStandarColor = 7;

	const void DisplayText();
	const void AddButton(Button* newButton);
	const void InsertButton(int yPos, Button* newButton);
	const int GetMenuLength();


};

