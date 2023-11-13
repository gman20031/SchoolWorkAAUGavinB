#include <iostream>
#include <windows.h>
#include <fstream>
#include <limit>


int main()
{
	char *myArray;

	std::getline(myArray , numeric_limits<streamsize>::max(), '0');

	std::cout << sizeof(map)-1 << std::endl;
	std::cout << (int)map[sizeof(map)-1] << std::endl;

	std::cout << 
	return 0;
}



