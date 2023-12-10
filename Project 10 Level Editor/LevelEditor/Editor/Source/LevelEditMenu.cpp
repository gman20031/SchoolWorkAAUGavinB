#include "../Header/LevelEditMenu.h"

#include <iostream> 
#include <algorithm> // clamp
#include <conio.h> // getch
#include <filesystem> //filepaths
#include <cctype> // toupper

#include "../../Editor.h"
#include "../../Game.h"

static const char goodCharacters[] =
{
	levelInfo::kEmptySpaceChar,
	levelInfo::kTrapChar,
	levelInfo::kWallChar,
	Player::kPlayerChar,
	(char)Enemy::enemyType::horizontol,
	(char)Enemy::enemyType::verticle,
	levelInfo::kExitChar,
};

LevelEditMenu::LevelEditMenu(std::filesystem::path* filePath)
{
	m_editedLevel.FillFromFile(filePath);
	m_currentFilePath = filePath;

	m_pTopButtons = (LevelButton*)calloc(kTopButtonLength, sizeof(LevelButton));
	m_pBottomButtons = (LevelButton*)calloc(kBotButtonLength, sizeof(LevelButton));
	if (m_pTopButtons == nullptr or m_pBottomButtons == nullptr)
	{
		exit(0);
	}
	m_currentSelectedChar = levelInfo::kWallChar;

	// witness - desperation and lazyness
	m_pTopButtons[0] = LevelButton(LevelButton::ButtonTypes::ChangeSelectedChar, "empty", this, levelInfo::kEmptySpaceChar);
	m_pTopButtons[1] = LevelButton(LevelButton::ButtonTypes::ChangeSelectedChar, "trap", this, levelInfo::kTrapChar);
	m_pTopButtons[2] = LevelButton(LevelButton::ButtonTypes::ChangeSelectedChar, "wall", this, levelInfo::kWallChar);
	m_pTopButtons[3] = LevelButton(LevelButton::ButtonTypes::ChangeSelectedChar, "player", this, Player::kPlayerChar);
	m_pTopButtons[4] = LevelButton(LevelButton::ButtonTypes::ChangeSelectedChar, "horizontal Enemy", this, (char)Enemy::enemyType::horizontol);
	m_pTopButtons[5] = LevelButton(LevelButton::ButtonTypes::ChangeSelectedChar, "Verticle Enemy", this, (char)Enemy::enemyType::verticle);
	m_pTopButtons[6] = LevelButton(LevelButton::ButtonTypes::ChangeSelectedChar, "Exit", this, levelInfo::kExitChar);


	m_pBottomButtons[0] = LevelButton(LevelButton::ButtonTypes::SaveToFile, "Save", this);
	m_pBottomButtons[1] = LevelButton(LevelButton::ButtonTypes::ReizeMap, "Resize", this);
	m_pBottomButtons[2] = LevelButton(LevelButton::ButtonTypes::ClearMap, "Clear", this);
	m_pBottomButtons[3] = LevelButton(LevelButton::ButtonTypes::ReturnToMenus, "Return", this);

	SetCursorLocation({ 0,0 });
}

LevelEditMenu::~LevelEditMenu()
{
	free( m_pTopButtons);
	free( m_pBottomButtons);
}


/////////////////////////////////
//// Button Functions
/////////////////////////////////

bool LevelEditMenu::ConfirmSelect()
{
	char inputChar;
	bool goodChar = false;
	for(;;)
	{
		do
		{
			std::cout << "\nplease confirm selection (y/n)\n";
			inputChar = _getch();
		} while (!std::cin.good());
		inputChar = toupper(inputChar);
		switch (inputChar)
		{
		case 'Y':
			return true;
		case 'N':
			return false;
		default:
			continue;
		}
	}
	return false;
}

// Changes the current character that will be places to the one specified
void LevelEditMenu::ChangeSelectedChar(char newChar)
{
	m_currentSelectedChar = newChar;
}

// Saves the current Level to the file given when editor was opened
bool LevelEditMenu::SaveToFile()
{
	if (!ConfirmSelect())
		return true;

	m_currentFile.open(*m_currentFilePath);
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
	if (!ConfirmSelect())
		return;

	std::cout << "\nPlease enter a width value" << '\n';
	int width = Inputs::GetMeAnInt();
	std::cout << "Please enter a height value" << '\n';
	int height = Inputs::GetMeAnInt();
	m_editedLevel.InitMap(width, height);
}

// Changes all characters in level to Wall Characters
void LevelEditMenu::ClearMap()
{
	if (!ConfirmSelect())
		return;

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
	if (!ConfirmSelect())
		return;

	m_keepEditing = false;
}

////////////////////////////////////////////
//// Cursor Functions
////////////////////////////////////////////

void LevelEditMenu::EnsureInBounds()
{
	m_cursorLocation.y = std::clamp(m_cursorLocation.y, 0, 1);
	if(m_cursorLocation.y == 0)
		m_cursorLocation.x = std::clamp(m_cursorLocation.x, 0, kTopButtonLength-1);
	else
		m_cursorLocation.x = std::clamp(m_cursorLocation.x, 0, kBotButtonLength-1);

}

void LevelEditMenu::MoveCursor(Direction direction)
{
	GetCurrentButtonSelection().m_isSelected = false;

	if (m_inMap)
	{
		m_editedLevel.MoveCursor(direction);
		if (m_editedLevel.GetSelectedLocation().y < 0)
		{
			m_inMap = false;
			m_editedLevel.MoveCursor(Direction::kDown);
			m_cursorLocation.y = 0;
			GetCurrentButtonSelection().m_isSelected = true;
		}
		if (m_editedLevel.GetSelectedLocation().y > m_editedLevel.GetMapHeight()-1)
		{
			m_inMap = false;
			m_editedLevel.MoveCursor(Direction::kUp);
			m_cursorLocation.y = 1;
			GetCurrentButtonSelection().m_isSelected = true;
		}
	}
	else
	{
		int tempY = m_cursorLocation.y;
		Inputs::MoveLocation(&m_cursorLocation, direction);
		EnsureInBounds();
		if (m_cursorLocation.y != tempY)
		{
			if (m_cursorLocation.x > 4)
				m_cursorLocation.x = 4;
			m_inMap = true;
		}
		else
			GetCurrentButtonSelection().m_isSelected = true;
	}
	

	
}

void LevelEditMenu::SetCursorLocation(Location target)
{
	m_cursorLocation = target;
	GetCurrentButtonSelection().m_isSelected = true;
}

void LevelEditMenu::HandleInteraction()
{
	if (m_inMap)
		m_editedLevel.SetAt(m_editedLevel.GetSelectedLocation(), m_currentSelectedChar);
	else
	{
		GetCurrentButtonSelection().EventHandler();
	}
}

Location* LevelEditMenu::GetCursorLocation()
{
	return &m_cursorLocation;
}

LevelButton& LevelEditMenu::GetCurrentButtonSelection()
{
	if (m_cursorLocation.y == 0)
		return m_pTopButtons[m_cursorLocation.x];
	else
		return m_pBottomButtons[m_cursorLocation.x];
}

////////////////////////////////////////////
//// Printing Functions
////////////////////////////////////////////

// Prints out the editor
void LevelEditMenu::PrintEditMenu()
{
	for (int i = 0; i < LevelEditMenu::kTopButtonLength; ++i)
	{
		if (m_pTopButtons[i].m_isSelected)
			m_pTopButtons[i].DisplayTextselected();
		else
			m_pTopButtons[i].DisplayText();
		std::cout << " | ";
	}
	std::cout << '\n';
	if (m_inMap)
		m_editedLevel.Display();
	else
		m_editedLevel.DisplayNoSelect();
	for (int i = 0; i < LevelEditMenu::kBotButtonLength; ++i)
	{
		if( m_pBottomButtons[i].m_isSelected)
			m_pBottomButtons[i].DisplayTextselected();
		else
			m_pBottomButtons[i].DisplayText();
		std::cout << " | ";
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// Button Class stuff

LevelButton::LevelButton(ButtonTypes button, const char* displayText,
						 LevelEditMenu* linkedMenu, char charChanger)
{	
	m_buttonFunction = button;
	m_linkedMenu = linkedMenu;
	m_charChanger = levelInfo::kWallChar;
	m_isSelected = false;

	m_displayText = displayText;
	for (char character : goodCharacters)
	{
		if(charChanger == character)
			m_charChanger = charChanger;
	}
		
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