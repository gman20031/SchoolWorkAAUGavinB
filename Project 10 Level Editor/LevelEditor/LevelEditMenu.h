#pragma once
#include <string>
#include <fstream>

#include "Level/LevelData.h"
#include "Menu.h"

class LevelButton;

class LevelEditMenu
{
	//"LevelData\CustomLevels\TESTFILE.txt"

	static constexpr int kTopButtonLength = 6;
	static constexpr int kBotButtonLength = 4;
	LevelButton* m_pTopButtons;
	LevelButton* m_pBottomButtons;
	levelInfo m_editedLevel;
	std::ofstream m_currentFile;
	std::string m_currentFilePath = "LevelData\\CustomLevels\\TESTFILE.txt";

	Location m_cursorLocation;

	bool m_keepEditing;
	bool m_inMap;
public:
	LevelEditMenu(const char* filePath);
	~LevelEditMenu();

	void ChangeSelectedChar(char newChar);
	bool SaveToFile();
	void ReizeMap();
	void ClearMap();
	void ReturnToMenus();

	void MoveCursor(Direction direction);
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
	LevelButton() = default;
	LevelButton(ButtonTypes button, const char* displayText,
				LevelEditMenu* linkedMenu, char charChanger = 0);


	void EventHandler();

	//std::string m_displayText; - inherited
	//bool m_isSelected; - inherited
	//void DisplayText() const; - inherited
	//void DisplayTextselected() const; - inherited

};