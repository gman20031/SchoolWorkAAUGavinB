/*
    The user starts with a score of 0 and must earn a score of 10 to win.
    The game is played in rounds. Each round:
       - Print the user's score.
       - Generate a random number between 1 and 20, inclusive (meaning both 1 and 20 should be possible numbers).
       - Print the random number.
       - Ask the user which of the following is correct:
            A. The number is a multiple of 2.
            B. The number is a multiple of 3.
            C. The number is a multiple of both 2 and 3.
            D. None of these are true.
    If the user gets the answer right, they gain a point.
    If the user gets the answer wrong, they lose a point.
    There is no penalty for losing points. The user's score can be negative and nothing will happen.
    The user wins when they get 10 points.

*/


#include <iostream>
#include <string>
#include <limits>
#include <time.h>

struct GameParameter
{
    int minRoll;
    int maxRoll;
    int winningScore;
    int *multiplesArray; //array
};

char GetMeChar() //get any single Ascii character
{
	char inputOne;
	bool badCharacter = true;

	std::cin >> inputOne;

	while (!std::cin.good()) //If one or both of the inputs were not compatiable, it will be false, and go to this while loop
	{
		std::cout << "That was not a proper response. Please input a character\n";
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> inputOne;
	}// while not good

	return inputOne;
}//get any single Ascii character

int GetRandomNumber(int min, int max) // gets you a random number, based on the min and max
{
    return min + rand() % ((max-min)+1); // random number based on the inputs

}//getRandomNumber

int CheckMultiples(int intChecked) //checks the number given to see if it is a multiple of every x numbers listed Within the function.
{
    
    return 0;
}// checks multiples

bool *CreateBooleanArray(int *multiplesArray)
{
    int arraySize = sizeof(multiplesArray);
    bool *booleanArray = (bool*)calloc(arraySize, sizeof(bool));

    if(arraySize > 0)
    { 
        for (int i = 0; i < arraySize; ++i)
        {
            booleanArray[i] = false;
        }

        return booleanArray;

    }

    // do something if multiples array is size 0 or less, cause that should never happen.

}//createboolArray

int MainGameLoop(GameParameter parameters) // the main game loop.
{
    int currentScore = 0, currentNumber = 0;
    bool correctAnswer = false;
    bool *isMultiples = CreateBooleanArray(parameters.multiplesArray);

    std::cout << isMultiples[0] << isMultiples[1];


     return 0;
}//main game loop

int main()
{
    constexpr int maxValue = 20, minValue = 1, winValue = 20;
    int allMultiples [2] = { 2 , 3 };
    GameParameter parameters = {minValue, maxValue, winValue, allMultiples};
    
    srand(time(0)); // seed RNG in main so it never repeats

    MainGameLoop(parameters);



    return 0;
}//main end