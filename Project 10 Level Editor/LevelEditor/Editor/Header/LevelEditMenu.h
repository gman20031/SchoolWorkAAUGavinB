#pragma once
#include <string>
#include <fstream>

#include "ExistingLevelMenu.h"
#include "Button.h"
#include "Menu.h"
#include "../../LocationAndDirection.h"
#include "../../Game/Header/LevelData.h"

class LevelButton;
//why the hell did I no derive this, its way more trouble than its worth not allocating empty space
class LevelEditMenu
{
	//"LevelData\CustomLevels\TESTFILE.txt"

	static constexpr int kTopButtonLength = 7;
	static constexpr int kBotButtonLength = 4;
	LevelButton* m_pTopButtons;
	LevelButton* m_pBottomButtons;
	levelInfo m_editedLevel;
	std::ofstream m_currentFile;
	std::filesystem::path* m_currentFilePath;

	void EnsureInBounds();
	bool ConfirmSelect();

	Location m_cursorLocation;
	char m_currentSelectedChar;
	bool m_inMap;

public:
	bool m_keepEditing = true;

	LevelEditMenu(std::filesystem::path* filePath);
	~LevelEditMenu();

	void ChangeSelectedChar(char newChar);
	bool SaveToFile();
	void ReizeMap();
	void ClearMap();
	void ReturnToMenus();

	void MoveCursor(Direction direction);
	void SetCursorLocation(Location target);
	void HandleInteraction();
	Location* GetCursorLocation();
	LevelButton& GetCurrentButtonSelection();

	void PrintEditMenu();
};

class LevelButton : public Button
{
public:
	enum class ButtonTypes
	{
		ChangeSelectedChar,
		SaveToFile,
		ReizeMap,
		ClearMap,
		ReturnToMenus,
	};

private:
	LevelEditMenu* m_linkedMenu;
	ButtonTypes m_buttonFunction;
	char m_charChanger;

public:
	LevelButton(ButtonTypes button, const char* displayText,
				LevelEditMenu* linkedMenu, char charChanger = 0);


	void EventHandler();

	//std::string m_displayText; - inherited
	//bool m_isSelected; - inherited
	//void DisplayText() const; - inherited
	//void DisplayTextselected() const; - inherited

};