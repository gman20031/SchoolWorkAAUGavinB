#include <iostream>
#include <stdlib.h>

void DoSomething();
void DoStatic();
void StaticExpanded();

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

	std::cout << std::endl;
	// this can be thought of as similair to how when you make a loop, 
	// initialzing the variable outside of the loop allow each loop to iterate further,
	// while initalizing a variable inside of a loop will cause it to be reset ever single loop
	int outside = 1;
	for (int i = 0; i < 3; ++i)
	{
		int inside = 1;

		++outside;
		++inside;

		std::cout << inside << " - ";
		std::cout << outside << std::endl;
	}
	// if the for loop was instead a function, what would happen here is that the variable inside would be created and set to 1
	// the adding would happen, inside would be printed, then inside would be removed from memory
	// then the next time it is called inside would be recreated and set to 1, then added and printed just like before.
	return 0;
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
