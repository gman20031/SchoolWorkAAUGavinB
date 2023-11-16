#include <iostream>
#include <stdlib.h>

void DoSomething();
void DoStatic();

int main()
{
	//--------------------------------------------------------------------------------------------------------
	// Quick example of scoping
	// When you call a function, that function has its own scope
	// so when the function is finished, everything withini that function is deleted and freed from memory

	// For example, in this do something function
	// It initializes the number 3, adds four, then prints
	for (int i = 0; i < 3; ++i)
	{
		DoSomething();
	}
	// Since the variable number, is scoped to the function. every time the function completes it deletes itself
	// Then the function re allocated and initalizes the variable to the integer 3
	// adds the 2 and prints it
	std::cout << std::endl;
	// If you want to get around variables deleting themselves, you can use static
	// Static tells the compiler to allocate the memory for this variable once
	// and not delete it until the program finishes.
	for (int i = 0; i < 3; ++i)
	{
		DoStatic();
	}
	// So because this is a statically allocated integer, it will not delete at function end
	// and neither will it reinialize itself to 3, the creation is only done once at compile time.
	// That causes this function to simply add 2 every time it is run and print that.
}

void DoSomething()
{
	int number = 3;
	number += 2;
	std::cout << number << std::endl;
}

void DoStatic()
{
	static int number = 3;
	number += 2;
	std::cout << number << std::endl;
}
