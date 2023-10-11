#include <iostream>
#include <string>
#include <cstdlib>

int main(){
	std::string name, race, profession ;

	std::cout << "Name? \n";
	std::cin >> name;

	std::cout << "race?\n";
	std::cin >> race;

	std::cout << "class?\n";
	std::cin >> profession;

	std:: cout << name << " the " << race << ' ' << profession;

	return 0;
}//main end