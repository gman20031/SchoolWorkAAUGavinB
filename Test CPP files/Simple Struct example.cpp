#include <iostream>

struct TestStruct // creates a data stucture called TestStruct, does not allocate any memory or do anything
{					// a struct effectively just creates our own data type
	int minimum; // this indicates this data stucture will include a memory block for an int, assigning a variable name of minimum
	int maximum; // same for maximum
	int* parray; // same but for an int pointer. which will then be used later as an array.
};

int main()
{
	int minimumVal = 0 , MaximumValue = 5;
	int testArray[3] = { 1, 2, 3 }; //creates some values to demonstrate

	TestStruct myStruct; // initilazes a variable of type test struct, named myStruct.
						// this is where it would allocate the memory required for everything in the struct
						// in this case, 2 ints and an int pointer
	myStruct = { minimumVal , MaximumValue, testArray }; // this then actually fills those places in memory.
					// much like any other data type, you could make all this one line.
					// since an array is effectively a pointer to the first place in memory of a chain of blocks
					// you are able to just set a pointer equal to an array and get similar usage, see array example.

	// to acess the parts of a struct use structName.variableName 
	std::cout << myStruct.parray << ' ' << myStruct.parray[0] << std::endl;
	std::cout << "minimum is " << ' ' << myStruct.minimum << std::endl;
	std::cout << "maximum is " << ' ' << myStruct.maximum << std::endl;

	return 0;
}//main