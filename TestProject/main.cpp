#include <iostream>
#include <string>


int main()
{
	int basesTotal, basesOwned;


	std::cout << "How many total bases\n";
	std::cin >> basesTotal;

	std::cout << "how many bases are owned\n";
	std::cin >> basesOwned;


	if (basesTotal == basesOwned) std::cout << "All your base are belong to us.\n";
	else if (basesOwned > 1) std::cout << "Some your base are belong to us.\n";
	else if (basesOwned == 1) std::cout << "One your base are belong to us.\n";
	else std::cout << "None your base are belong to us.";

	return 0;
}//main