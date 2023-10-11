/*
	Prompt the user for their name. Print the name back, saying hello.
	Prompt the user for two numbers. Add them, then print the result.
	Prompt the user for two new numbers. Subtract one from the other, then print the result.
	Prompt the user for two new numbers. Multiply them, then print the result.
	Prompt the user for two new numbers. Divide one by the other, then print the result.
	Prompt the user for two new integers. Print the modulus of one number by the other.
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

float GetMeTwoFloats(float *firstNumber, float *secondNumber) // grabs two floats from user input, checks if float, then sets the firstNumber and secondNumber variables in main to the input variables. 
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

int GetMeTwoInts(int *firstInteger, int *secondInteger) // Does the same as the float function but grabs integers for the modulo stuff specifically.
{
	int inputOne, inputTwo = 0; // this is all the same as above

	std::cin >> inputOne >> inputTwo;

	while (!std::cin.good()) 
	{
		std::cout << "one or more of those were not integers \n";
		std::cin.clear();													
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
		std::cin >> inputOne >> inputTwo;
	}//test for ints

	*firstInteger = inputOne;	
	*secondInteger = inputTwo;	

	return 0;
}//GetMeTwoInts func

int main()
{
	std::string userName; //string for name, first variable
	float firstNumber, secondNumber = 0.0f; // floats for almost all math, second and third variables
	int firstInteger, secondInteger = 0; // ints for modulo stuff // fourth and fifth variables
	//int multipleOne, MultipleTwo = 0;//variables just for the last section
	


	//Ask use for name
	std::cout << "Hello, welcome to the simple calculator. Lets start off by asking, what is your name? \n";
	std::getline(std::cin, userName);
	std::cout << "Sweet, well " << userName << " this should be good\n";

	// add two numbers
	std::cout << "\nFirst thing we are doing is adding two numbers together \n"
			  << "which two numbers would you like to add together? \n (when inputing two numbers for this calculator, just input, \"first number, a space, second number\") \n ";
	GetMeTwoFloats(&firstNumber, &secondNumber);
	std::cout << firstNumber << " + " << secondNumber << " = ";
	firstNumber += secondNumber;
	std::cout << firstNumber << '\n';
	
	//sub two numbers
	std::cout << "\nNow, we are going to subtract two numbers \n"
			  << "Which numbers are we subtracting (x - y) \n";
	GetMeTwoFloats(&firstNumber, &secondNumber);
	std::cout << firstNumber << " - " << secondNumber << " = ";
	firstNumber -= secondNumber;
	std::cout << firstNumber << '\n';

	//multiple two numbers
	std::cout << "\nNow, we are going to multiply two numbers \n"
			  << "Which numbers are we multiplying (x * y) \n";
	GetMeTwoFloats(&firstNumber, &secondNumber);
	std::cout << firstNumber << " * " << secondNumber << " = ";
	firstNumber *= secondNumber;
	std::cout << firstNumber << '\n';

	//divide two numbers
	std::cout << "\nNow, we are going to divide two numbers \n"
			  << "Which numbers are we dividing (x / y) \n";
	GetMeTwoFloats(&firstNumber, &secondNumber);
	std::cout << firstNumber << " / " << secondNumber << " = ";
	firstNumber /= secondNumber;
	std::cout << firstNumber << '\n';

	// Modulo two ints
	std::cout << "\nAight, funny one, lets find the modulo of two numbers\n"
			  << "Which numbers are we Moding, integers only (x % y) \n";
	GetMeTwoInts(&firstInteger, &secondInteger);
	std::cout << firstInteger << " % " << secondInteger << " = ";
	firstInteger %= secondInteger;
	std::cout << firstInteger << '\n';

	// Least Common multiple
	std::cout << "\nLast one, we are going to find the least common multiple of two numbers\n"
			  << "Which numbers are we picking? integers only.\n";
	GetMeTwoInts(&firstInteger, &secondInteger);
	firstNumber = (float)firstInteger; // to maintain only 5 variables in main I am using my floats as the variables for this step. I would idealy create two more ints just for this purpose, as seen above I commented out the two ints.
	secondNumber = (float)secondInteger;

	while (firstNumber != secondNumber)  // if the multiples are not the same, increase the multiple by +1 of whichever is smaller.
	{
		if (firstNumber < secondNumber)  firstNumber += firstInteger;
		else secondNumber += secondInteger;
	}//while not equal end
	std::cout << "the lowest common multiple of " << firstInteger << " and " << secondInteger << " is " << firstNumber << '\n';

	return 0;
}//main end