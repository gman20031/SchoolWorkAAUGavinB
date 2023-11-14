#include <iostream>
#include <vector>
#include <fstream> // for filereading
#include <string> 

void GetMapStrings(std::vector<std::string>* maps)
{
	std::fstream myfile;
	myfile.open("Maps.txt");
	if (myfile.is_open())
	{
		std::string tempString = "0";

		while (getline(myfile, tempString, '0'))
		{
			if (myfile.eof())
				break;
			maps->push_back(tempString);
		}

		myfile.close();
	}
	else
	{
		std::cout << "your -redacted- trash lol ";
	}
}


int main()
{

	std::vector<std::string> allMaps; // get all maps 
	GetMapStrings(&allMaps);

	return 0;
}