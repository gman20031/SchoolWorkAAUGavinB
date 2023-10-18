#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>

float GetMeTwoFloats(float* pfirstNumber, float* psecondNumber) // grabs two floats from user input, checks if float, then sets the firstNumber and secondNumber variables in main to the input variables. 
{												
							/*
								The float* pfirstNumber is saying that first variabe recieved is a floating point number pointer. the * means pointer, and the p prefix also is a reminder
								The pointer means that if this is called, it is pointing at the recieved adress in memory.
								If I just send a variable like normal, say int first number, and recieved an int, I would create a whole new slot in memory and copy the int i recieved
								This way, I revieve the exact location in memory that the float in the main function is located.
								Then when later I change *pfirstNumber to something, it literally goes to the place pointed to, and changes that adress of memory to what I tell it to.
					
							*/

	float inputOne, inputTwo = 0.0f; //creates two temp variables to grab the inputs

	std::cin >> inputOne >> inputTwo;

	while (!std::cin.good()) //If one or both of the inputs were not compatiable, it will be false, and go to this while loop
	{
		std::cout << "one or more of those were not proper numbers \n";
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> inputOne >> inputTwo;
	}//test for floats

	*pfirstNumber = inputOne;	//changes firstNumber variable in main
	*psecondNumber = inputTwo;	//changes secondNumber variable in main
		//because of the *, It means I am telling the computer the exact adress to change. 
		//It's exactly the same as a normal variable = variable, except I just want to keep the same location in memory from main

	return 0.0f;
}// get two floats func

int GetMeInteger()
{
	int userIntInput;

	std::cin >> userIntInput;

	while (!std::cin.good()) // if input is not good for any reason loop
	{
		std::cout << "Please enter an integer only \n";
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> userIntInput;
	}//test for floats

}

int main()
{
	float numberOne, numberTwo = 10;

	GetMeTwoFloats(&numberOne, &numberTwo); // Sends the ADRESS of both numberOne and numberTwo to the function of GetMeTwoFloats();

	return 0
}