
#include <iostream>
using namespace std;

int main()
{
	std::string battleshipArray[] {"Water", "Water", "Battleship", "Water", "Battleship", "Water"};
	int input;
	std::cin >> input;
	if(battleshipArray[input] == "Battleship")
		std::cout << "You sank my battleship." << std::endl;
	else
		std::cout << "You missed." << std::endl;
	return 0;
}