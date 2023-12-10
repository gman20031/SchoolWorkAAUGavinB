#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <filesystem>

#include "Editor.h"
#include "Game.h"

void GotoFirstMenu(std::vector<Menu*>* menuStack);
void CreateNewLevel(std::vector<Menu*>* menuStack);
void EditExistingLevel(std::vector<Menu*>* menuStack);
void GoBackButton(std::vector<Menu*>* menuStack);
bool AddAllExistingLevels(ExistingLevelMenu* levelsMenu);

int main(int argc, char* argv[])
{
	std::vector<Menu*> menuStack;
																					// Notice here, how I thought I would add more subfolders
	Menu baseMenu("Maze Game \nArrow keys and Press 'e' to interact\nlevels saved to /leveldata/CustomLevels", nullptr);
	MenuButton B_gotoEditMenu("Edit Levels", &GotoFirstMenu);
	baseMenu.AddButtonNewLine(&B_gotoEditMenu);
	baseMenu.SetCursorLocation({ 0,0 }); // this is bad, but I need to finish this QUICK -- coming to the is message later... I spent another probably 12 hours to get to this state.
	menuStack.push_back(&baseMenu);


	Menu editorMenu("Edit Level", &baseMenu);
	MenuButton B_createNewLevel("New Level", &CreateNewLevel);
	MenuButton B_editExistingLevel("Edit Existing", &EditExistingLevel);
	MenuButton B_goBack("return", &GoBackButton);
	editorMenu.AddButtonNewLine(&B_createNewLevel);
	editorMenu.AddButtonNewLine(&B_editExistingLevel);
	editorMenu.AddButtonNewLine(&B_goBack);
	editorMenu.SetCursorLocation({ 0,0 });

	

	for (;;)
	{
		system("cls");
		menuStack.back()->DisplayAllText();
		char input = _getch();
		if (input == 'e')
			menuStack.back()->PressSelectedButton(&menuStack);
		else if (input == Inputs::kSpecialWindowKey)
		{
			Direction dir = Inputs::GetDirFromArrowKey();
			menuStack.back()->MoveCursor(dir);
		}
	}

	return 0;
}

void GoBackButton(std::vector<Menu*>* menuStack)
{
	menuStack->pop_back();
}

void GotoFirstMenu(std::vector<Menu*>* menuStack)
{
	menuStack->push_back(menuStack->back()->GetSubMenu(0));
}

void CreateNewLevel(std::vector<Menu*>* menuStack)
{
	std::ofstream file;

	std::string pathStr = "LevelData\\CustomLevels\\";
	std::string fileName;
	do
	{
		system("cls");
		std::cout << "please enter a name for the level\nThis level will automatically be added to CustomLevels folder\nTo delete, go there, I wont at this point\n";
	} while (!Inputs::SetStringFromUser(fileName));

	pathStr += fileName += ".txt";

	std::filesystem::path filePath = pathStr;

	file.open(filePath);
	file << '#';
	file.close();

	//hack AF
	LevelMenuButton B(&filePath);
	B.EventHandler();

}

void EditExistingLevel(std::vector<Menu*>* menuStack)
{
	ExistingLevelMenu existingLevelMenu("All Levels in CustomLevels\nI messed up, so X goes back", menuStack->back());
	if (!AddAllExistingLevels(&existingLevelMenu))
	{
		system("cls");
		std::cout << "No files in CustomLevels Folder,\n";
		system("pause");
		return;
	}
	for (;;)
	{
		system("cls");
		existingLevelMenu.DisplayAllText();
		char input = _getch();
		if (input == 'e')
			existingLevelMenu.PressSelectedButton();
		if (input == 'x')
			break;
		else if (input == Inputs::kSpecialWindowKey)
		{
			Direction dir = Inputs::GetDirFromArrowKey();
			existingLevelMenu.MoveCursor(dir);
		}
	}
}

bool AddAllExistingLevels(ExistingLevelMenu* levelsMenu)
{
	if (std::filesystem::is_empty("..\\LevelEditor\\LevelData\\CustomLevels"))
		return false;

	for (const auto& entry : std::filesystem::directory_iterator("..\\LevelEditor\\LevelData\\CustomLevels"))
	{
		levelsMenu->AddButtonNewLine(&entry.path());
	}
	
	levelsMenu->SetCursorLocation({ 0,0 });
	return true;
}

