#pragma once
#include <string>
#include <functional>

#include "LocationAndDirection.h"
#include "Button.h"
#include "Level/levelData.h"
class Menu;



class MenuButton : public Button
{
protected:
	std::function<void(std::vector<Menu*>&)> m_eventFunction;


public:
	MenuButton(const char* name, std::function<void(std::vector<Menu*>&)> eventFunction);
	void EventHandler(std::vector<Menu*>& menuStack) const;
};

class Menu
{
protected:
	Menu* m_rootMenu;
	std::vector<Menu*> m_subMenus;
	std::string m_menuTitle;
	std::vector<std::vector<MenuButton*>> m_buttonGrid;
	Location m_targetButtonLocation;

	MenuButton* GetButtonAt(Location target);
	void EnsureInBounds();

public:
	
	static constexpr int kRedColor = 4;
	static constexpr int kStandarColor = 7;

	Menu(const char* title, Menu* rootMenu);
	void AddSubMenu(Menu* newSubMenu);
	Menu* GetSubMenu(int index);

	void DisplayAllText() const ;

	void AddButtonNewLine(MenuButton* newButton) ;
	void InsertButton(int xPos, int yPos , MenuButton* newButton) ;
	size_t GetMenuLength() const;
	size_t GetLegthAtY(int yPos) const;

	void SetCursorLocation(Location newLocation);
	void MoveCursor(Direction direction);
	Location* GetTargetLocation();
	void PressSelectedButton(std::vector<Menu*>& menuStack);
};

