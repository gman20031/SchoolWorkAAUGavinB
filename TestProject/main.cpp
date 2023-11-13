#include <iostream>
#include <vector>
#include <string.h>
#include <cstring>
#include "Header.h"



int main() {
	// Call the function to get the vector
	std::vector<MyStruct> mainVector = createAndFillVector();

	// Access and print the elements of the main vector
	for (const MyStruct& s : mainVector) {
		std::cout << "myInt: " << s.myInt << ", myCharPointer: " << s.myCharPointer << std::endl;

		// Don't forget to free the allocated memory
		delete[] s.myCharPointer;
	}

	return 0;
}