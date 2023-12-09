#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

std::string rootPath = "..\\Project 10 Level Editor\\LevelEditor\\LevelData\\CustomLevels";

void RemoveRootPath(std::string& changingString, std::string& rootPath)
{
	changingString.erase(0, rootPath.size());
}

int main()
{
	for (const auto& entry : std::filesystem::directory_iterator("..\\LevelEditor\\LevelData\\CustomLevels"))
	{
		std::string temp = entry.path().filename().string();
		std::cout << temp << '\n';

	}
	return 0;
}

