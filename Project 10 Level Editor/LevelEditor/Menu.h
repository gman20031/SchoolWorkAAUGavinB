#pragma once
#include <string>
#include <functional>

#include "Level/levelData.h"
class Menu;

class Button
{
protected:
	std::string m_displayText;
	//Menu*		m_rootMenu;
	std::function<void(Menu*)> m_eventFunction;
	

public:
	bool m_isSelected;

	Button(const char* name, std::function<void(Menu*)> eventFunction);

	void DisplayText() const;
	void DisplayTextselected() const;
	void EventHandler(Menu* currentMenu) const;
};

class Menu
{
protected:
	Menu* m_rootMenu;
	std::vector<Menu*> m_subMenus;
	std::string m_menuTitle;
	std::vector<std::vector<Button*>> m_buttonGrid;
	location m_targetButtonLocation;

	Button* GetButtonAt(location target);
	void EnsureInBounds();

public:
	static enum class Direction {
		kUp,
		kDown,
		kLeft,
		kRight,
	};
	
	static constexpr int kRedColor = 4;
	static constexpr int kStandarColor = 7;

	Menu(const char* title, Menu* rootMenu);
	void AddSubMenu(Menu* newSubMenu);
	Menu* GetRootMenu();
	Menu* GetSubMenu(int index);

	void DisplayAllText() const ;

	void AddButtonNewLine(Button* newButton) ;
	void InsertButton(int xPos, int yPos , Button* newButton) ;
	size_t GetMenuLength() const;
	size_t GetLegthAtY(int yPos) const;

	void SetCursorLocation(location newLocation);
	void MoveCursor(Direction direction);
	void PressSelectedButton(Menu* currentMenu);
};

