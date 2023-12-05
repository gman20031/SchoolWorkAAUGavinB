#include <iostream>

class level
{
public:
	char* mapArray;

	char* at(int index) 
	{
		return &(mapArray[index]);
	}
	void printMap()
	{
		for (int i = 0; i < 5; ++i)
			std::cout << mapArray[i];
		std::cout << std::endl;
	}
};

int main()
{
	level testLevel;
	testLevel.mapArray = new char[5];
	for (int i = 0; i < 5; ++i)
		testLevel.mapArray[i] = 'a';
	testLevel.printMap();
	*testLevel.at(0) = 'b';
	testLevel.printMap();
	std::cout << *testLevel.at(1);
	return 0;
}