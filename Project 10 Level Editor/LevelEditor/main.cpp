#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

#include "Level/LevelData.h"
#include "Menu.h"
#include "LevelEditMenu.h"

constexpr int kSpecialWindowsKey = -32;

void HandleArrowKey(Menu* currentMenu);
static void GotoMenuOne(Menu* currentMenu);
static void DummyFunction(Menu* currentMenu);
static void GotoRootMenu(Menu* currentMenu);

class Displayer
{
public:
	Menu* currentMenu;

};

int main(int argc, char* argv[])
{
	//levelInfo levelOne(4,4);

	Menu testMenu("test", nullptr);
	Menu subMenuTest("sub Menu One", &testMenu);
	testMenu.AddSubMenu(&subMenuTest);

	Menu* currentMenu = &testMenu;

	Button SubMenuButtonOne("sub Menu One", &GotoMenuOne);
	Button returnButton("Return", &GotoRootMenu);

	Button dummyButton1("dummy", &DummyFunction);
	Button dummyButton2("dummy", &DummyFunction);

	testMenu.AddButtonNewLine(&dummyButton1);
	testMenu.AddButtonNewLine(&SubMenuButtonOne);

	subMenuTest.AddButtonNewLine(&dummyButton1);
	subMenuTest.InsertButton(1, 0, &dummyButton2);
	subMenuTest.AddButtonNewLine(&returnButton);

	testMenu.SetCursorLocation({ 0,0 });
	subMenuTest.SetCursorLocation({ 0,0 });
	for (;;)
	{
		system("cls");
		currentMenu->DisplayAllText();
		char input = _getch();
		if (input == 'e')
			currentMenu->PressSelectedButton(currentMenu);
		else if (input == kSpecialWindowsKey)
		{
			HandleArrowKey(currentMenu);
		}
	}

	return 0;
}

static void GotoMenuOne(Menu* currentMenu)
{
	currentMenu = currentMenu->GetSubMenu(0);
}

static void DummyFunction(Menu* currentMenu)
{

}

static void GotoRootMenu(Menu* currentMenu)
{
	currentMenu = currentMenu->GetRootMenu();
}


void HandleArrowKey(Menu* currentMenu)
{
	enum arrowKeys {
		right = 77,
		down = 80,
		up = 72,
		left = 75
	};

	char dummyChar = _getch();
	switch (dummyChar)
	{
	case arrowKeys::right:
		currentMenu->MoveCursor(Menu::Direction::kRight);
		break;
	case arrowKeys::down:
		currentMenu->MoveCursor(Menu::Direction::kDown);
		break;
	case arrowKeys::up:
		currentMenu->MoveCursor(Menu::Direction::kUp);
		break;
	case arrowKeys::left:
		currentMenu->MoveCursor(Menu::Direction::kLeft);
		break;
	}
}