#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

float GetMeTwoFloats(float* firstNumber, float* secondNumber) // grabs two floats from user input, checks if float, then sets the firstNumber and secondNumber variables in main to the input variables. 
{																// this isnt exactly neccary so I dont think the extra variables used here or at the end count towards my 5 variable limit.
	float inputOne, inputTwo = 0.0f; //creates two temp variables to grab the inputs

	std::cin >> inputOne >> inputTwo;

	while (!std::cin.good()) //If one or both of the inputs were not compatiable, it will be false, and go to this while loop
	{
		std::cout << "one or more of those were not proper numbers \n";
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> inputOne >> inputTwo;
	}//test for floats

	*firstNumber = inputOne;	//changes firstNumber variable in main
	*secondNumber = inputTwo;	//changes secondNumber variable in main

	return 0.0f;
}// get two floats func

int GetMeTwoInts(int* firstInteger, int* secondInteger) // Does the same as the float function but grabs integers for the modulo stuff specifically.
{
	int inputOne, inputTwo = 0; // this is all the same as above

	std::cin >> inputOne >> inputTwo;

	while (!std::cin.good())
	{
		std::cout << "one or more of those were not integers \n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	*firstInteger = inputOne;
	*secondInteger = inputTwo;

	return 0;
}//GetMeTwoInts func

int main()
{
	float numberOne, numberTwo = 10;

	GetMeTwoFloats(&numberOne, &numberTwo);

	return 0
}