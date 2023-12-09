#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <filesystem>

#include "Level/LevelData.h"
#include "Menu.h"
#include "LevelEditMenu.h"
#include "Inputs.h"

constexpr int kSpecialWindowsKey = -32;

void GotoEditMenu(std::vector<Menu*>& menuStack);
void CreateNewLevel(std::vector<Menu*>& menuStack);
void EditExistingLevel(std::vector<Menu*>& menuStack);
void AddAllExistingLevels(Menu& levelsMenu);

int main(int argc, char* argv[])
{
	std::vector<Menu*> menuStack;

	Menu baseMenu("Maze Game \n press 'e' to interact", nullptr);
	MenuButton B_gotoEditMenu("Edit Levels", &GotoEditMenu);
	menuStack.push_back(&baseMenu);

	Menu editorMenu("Edit Level", &baseMenu);
	MenuButton B_createNewLevel("New Level", &CreateNewLevel);
	MenuButton B_editExistingLevel("Edit Existing", &EditExistingLevel);

	Menu existingLevelsMenu("Existing Levels", &editorMenu);
	AddAllExistingLevels(existingLevelsMenu);

	for (;;)
	{
		system("cls");
		menuStack.back()->DisplayAllText();
		char input = _getch();
		if (input == 'e')
			menuStack.back()->PressSelectedButton(menuStack);
		else if (input == kSpecialWindowsKey)
		{
			Inputs::HandleArrowKey(menuStack.back()->GetTargetLocation());
		}
	}

	return 0;
}

void GotoFistMenu(std::vector<Menu*>& menuStack) 
{
	menuStack.push_back(menuStack.back()->GetSubMenu(0));
}

void CreateNewLevel(std::vector<Menu*>& menuStack)
{
	std::ofstream file;
	file.open("hello");
	file << '#';

}
void EditExistingLevel(std::vector<Menu*>& menuStack)
{

}
void AddAllExistingLevels(Menu& levelsMenu)
{

}

//for (const auto& entry : std::filesystem::directory_iterator("..\\LevelEditor\\LevelData\\CustomLevels"))
//{
//	std::string temp = entry.path().filename().string();
//	std::cout << temp << '\n';
//}