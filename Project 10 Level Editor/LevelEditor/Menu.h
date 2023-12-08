#pragma once
#include <string>
#include <functional>

#include "Level/levelData.h"
class Menu;

class Button
{
protected:
	std::string m_displayText;
	Menu*		m_rootMenu;
	std::function<void()> m_eventFunction;

public:
	Button(std::string name , std::function<void()> eventFunction);

	void DisplayText() const;
	void DispalyTextselected() const;
	void EventHandler() const;
};


class Menu
{
protected:
	Menu* m_rootMenu;
	std::string m_menuTitle;
	std::vector<Button*> m_allButtons;

public:
	static constexpr int kSelectedColor = 4;
	static constexpr int kStandarColor = 7;

	void DisplayText() const ;

	void AddButton(Button* newButton);
	void InsertButton(int index, Button* newButton);
	size_t GetMenuLength() const;


};

