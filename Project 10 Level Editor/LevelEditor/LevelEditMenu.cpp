
#include <iostream>

#include "LevelEditMenu.h"
#include "Inputs.h"
#include "Level/LevelData.h"
#include "Game/Player.h"
#include "Game/Enemy.h"

//wtf is this stop
static const char goodCharacters[] =
{
	levelInfo::kEmptySpaceChar,
	levelInfo::kTrapChar,
	levelInfo::kWallChar,
	Player::kPlayerChar,
	(char)Enemy::enemyType::horizontol,
	(char)Enemy::enemyType::verticle,
};

LevelEditMenu::LevelEditMenu(const char* filePath)
{
	m_pTopButtons = new LevelButton[kTopButtonLength];
	m_pBottomButtons = new LevelButton[kBotButtonLength];

	for (int i = 0; i < kTopButtonLength; ++i)
	{
		m_pTopButtons[i] = LevelButton( LevelButton::ButtonTypes::ChangeSelectedChar, &goodCharacters[i], this, goodCharacters[i] );
	}
	m_pBottomButtons[0] = LevelButton(LevelButton::ButtonTypes::SaveToFile, "Save", this);
	m_pBottomButtons[1] = LevelButton(LevelButton::ButtonTypes::ReizeMap, "Resize", this);
	m_pBottomButtons[2] = LevelButton(LevelButton::ButtonTypes::ClearMap, "Clear", this);
	m_pBottomButtons[3] = LevelButton(LevelButton::ButtonTypes::ReturnToMenus, "Return", this);

}

LevelEditMenu::~LevelEditMenu()
{
	delete[] m_pTopButtons;
	delete[] m_pBottomButtons;
}


/////////////////////////////////
//// Button Functions
/////////////////////////////////

// Changes the current character that will be places to the one specified
void LevelEditMenu::ChangeSelectedChar(char newChar)
{
	m_editedLevel.SetAt(m_cursorLocation, newChar);
}

// Saves the current Level to the file given when editor was opened
bool LevelEditMenu::SaveToFile()
{
	m_currentFile.open(m_currentFilePath);
	if (m_currentFile.is_open())
	{
		m_editedLevel.WriteToFile(this->m_currentFile);
		m_currentFile.close();
		return true;
	}
	else
		return false;
}

// Reizes the level to given parameters
void LevelEditMenu::ReizeMap()
{
	std::cout << "Please enter a width value" << '\n';
	int width = Inputs::GetMeAnInt();
	std::cout << "Please enter a height value" << '\n';
	int height = Inputs::GetMeAnInt();
	m_editedLevel.InitMap(width, height);
}

// Changes all characters in level to Wall Characters
void LevelEditMenu::ClearMap()
{
	int height = m_editedLevel.GetMapWidth();
	int width = m_editedLevel.GetMapHeight();

	for (int i = 0; i < height; ++i)
	{
		for (int n = 0; n < width; ++n)
		{
			m_editedLevel.SetAt({ n,i }, levelInfo::kWallChar);
		}
	}
}

// Stops Editing
void LevelEditMenu::ReturnToMenus()
{
	m_keepEditing = false;
}

////////////////////////////////////////////
//// Cursor Functions
////////////////////////////////////////////

void LevelEditMenu::MoveCursor(Direction direction)
{
	if (m_inMap)
		m_editedLevel.MoveCursor(direction);
	else
		Inputs::MoveLocation(&m_cursorLocation, direction);
}

////////////////////////////////////////////
//// Printing Functions
////////////////////////////////////////////

// Prints out the editor
void LevelEditMenu::PrintEditMenu()
{
	for (int i = 0; i < LevelEditMenu::kTopButtonLength; ++i)
	{
		std::cout << "| ";
		if (m_pTopButtons[i].m_isSelected)
			m_pTopButtons[i].DisplayTextselected();
		else
			m_pTopButtons[i].DisplayText();
		std::cout << " |";
	}
	std::cout << '\n';
	m_editedLevel.Display();
	for (int i = 0; i < LevelEditMenu::kBotButtonLength; ++i)
	{
		std::cout << "| ";
		if( m_pBottomButtons[i].m_isSelected)
			m_pBottomButtons[i].DisplayTextselected();
		else
			m_pBottomButtons[i].DisplayText();
		std::cout << " |";
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// Button Class stuff

LevelButton::LevelButton(ButtonTypes button, const char* displayText,
						 LevelEditMenu* linkedMenu, char charChanger)
{	
	m_buttonFunction = button;
	m_linkedMenu = linkedMenu;

	m_displayText = displayText;
	for (auto character : goodCharacters)
	{
		if(charChanger == character)
			m_charChanger = charChanger;
	}
	if (m_charChanger == 0)
		m_charChanger = '?';
		
}

void LevelButton::EventHandler()
{
	switch (m_buttonFunction)
	{
		case ButtonTypes::ChangeSelectedChar:
			m_linkedMenu->ChangeSelectedChar(m_charChanger);
			break;
		case ButtonTypes::SaveToFile:
			m_linkedMenu->SaveToFile();
			break;
		case ButtonTypes::ReizeMap:
			m_linkedMenu->ReizeMap();
			break;
		case ButtonTypes::ClearMap:
			m_linkedMenu->ClearMap();
			break;
		case ButtonTypes::ReturnToMenus:
			m_linkedMenu->ReturnToMenus();
			break;
	}
}