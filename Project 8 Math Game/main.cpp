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
#include <iostream> // allow input output
#include <string> // gives me string (class?) even though I dont use it fully lol
#include <limits> // to clear I/o Stream
#include <time.h> // for Srand
#include <cstdarg> // for variable length parameters in function
#include <locale> // to uppercase / lowercase characters

//Dont do these I assume? toConsole should have only beeen used for debug purposes, but it was so easy to use everywhere
#define toConsole(str) std::cout << str << std::endl //This is probably one of the only times I just do something cause its simple
#define specialSlotsCount 2 // dont know differences between this and public const int

struct GameParameter
{
	//Struct of all the game parameters so passing information is easy.
    int minRoll;
    int maxRoll;
    int winningScore;
	int multiplesCount;
    int *multiplesArray; //array
}; // game parameter struct

struct IntAndBool
{
	// struct of an int and a bool to allow for the parrellel array
	int multiple;
	bool isMultiple;
};//Int and Bool Struct

char GetMeChar()
{
	//Returns a single Ascii Character inputed from user. More than one input is ignored
	//Side effects: cin is cleared
	//Side effects: Prompts user if they did not input proper character
	char inputOne;

	std::cin >> inputOne;

	while (!std::cin.good()) //If one or both of the inputs were not compatiable, it will be false, and go to this while loop
	{
		std::cout << "That was not a proper response. Please input a character\n";
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> inputOne;
	}// while not good

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return inputOne;
}//get any single Ascii character

char GetMeYesNo()// get the variable I want to change, make sure its a character
{
	//Returns: A single 'y' or 'n'. will return NULL if failure to run code properly
	//Note:infinite loop potential
	//Side effect: runs getChar function so will clear input buffer
	//Side effect: prompt user if y or n is not inputed
	char response = GetMeChar();
	bool badChar = true;

	while (badChar) // while not a valid response, loops forever.
	{
		if (response == 'y' or response == 'n') //check if y or n
			return response;
		else
		{
			toConsole("Please input only y or n, nothing more");
			response = GetMeChar();
		}
	}

	return -1;
}//get Yes No

int GetMeInteger()
{
	//Returns an integer from cin
	//if not proper int will prompt user
	int userIntInput;

	std::cin >> userIntInput;

	while (!std::cin.good()) // if input is not good for any reason loop
	{
		std::cout << "Please enter an integer only \n";
		std::cin.clear();													// Resets all error flags from cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
		std::cin >> userIntInput;
	}//loop for bad int

	return userIntInput;
}

int GetRandomNumber(int min, int max) // gets you a random number, based on the min and max
{
    return min + rand() % ((max-min)+1); // random number based on the inputs

}//getRandomNumber

int CheckMultiples(int intChecked, IntAndBool* pisMultiples, int totalMultiples) 
{ // returns 0, will check the int checkeed againts every int within the array of IntAndBools to see if it is a multiple
  // then set the bool in that intandBool to the correct value
	int currentMultiple = 0;

	for (int i = 0; i < totalMultiples; ++i)
	{
		currentMultiple = pisMultiples[i].multiple;
		pisMultiples[i].isMultiple = (intChecked % currentMultiple == 0);
	}

	return 0;
}// checks multiples

IntAndBool* CreateParrallelBooleanArray(GameParameter parameters) // creates an array of int and bool structs, of length defined by parameters
{
	//This function first creates an array, with size equal to the number of multiples defined by parameters
	//each element the size of an int and bool data struct, then fills them with the correct multiple and false
	IntAndBool* pcreatedArray = (IntAndBool*)calloc((parameters.multiplesCount), sizeof(IntAndBool));

	if (pcreatedArray == NULL)
		return NULL;
	for (int i = 0; i < parameters.multiplesCount; ++i)
	{
		IntAndBool tempStruct = { parameters.multiplesArray[i], false };
		pcreatedArray[i] = tempStruct;
	}//fill array loop												

	return pcreatedArray;
}//createboolArray

void PrintIntroSequence(GameParameter parameters)
{
	// this function outputs the whole intro sequence based on the current parameters of the game
	// it will not change anything, other than the look of the console
	system("cls");
	toConsole("Hello, welcome to the Math Game");
	std::cout << "Your goal here is to get " << parameters.winningScore << " total points" << std::endl;
	std::cout << "You will be given a random number between " << parameters.minRoll
			  << " and " << parameters.maxRoll << std::endl;
	toConsole("you must then determine if that random number is a multiple of ");
	for (int i = 0; i < parameters.multiplesCount; ++i)
		std::cout << "    " << parameters.multiplesArray[i] << std::endl;
	toConsole("    multiple of the above");
	toConsole("or  none of the above");
	toConsole("if you are correct you gain a point. If you are wrong, you lose a point.");
	
	system("pause");
	return;
}//Intro

int PrintGameOptions(GameParameter parameters)
{	
	//Returns 0, prints all the options available from user given paramaters.
	char selectorChar = 'A';
	int totalOptions = parameters.multiplesCount + 2; // 2 is for the option of 'none of' and 'all of'
	int noneOfSlot = totalOptions - 1; // none of will apear last
	int allOfSlot = totalOptions - 2; // all of wil apear 2nd from last

	std::cout << "Is this a multiple of:" << std::endl;

	for (int i = 0; i < totalOptions; ++i)
	{
		std::cout << selectorChar << ": ";
		++selectorChar; // this will always be a capital letter since the loop cannot exceed the number of possible capital letters

		if (i == noneOfSlot) //special case for the none of text
		{
			std::cout << "none of the above" << std::endl;
			continue;
		}
		if (i == allOfSlot) // special case for the all of text
		{
			std::cout << "multiple of the above" << std::endl;
			continue;
		}
		std::cout << parameters.multiplesArray[i] << std::endl; // the numer we are talking about
	}
	return 0;
}//print game options

void PrintAnswer(IntAndBool* answerKey, int numberOfMultiples, int answerKeyLength)
{
	//does not return anything, prints the correct answer to current game loop
	// given the answer, total number of multiples, and answerKeyLength
	toConsole("the correct answer was");

	if (numberOfMultiples == 0)
		toConsole("your number is a multiple of none of these");
	else
	{
		std::cout << "your number is a multiple of: " << std::endl;
		for (int i = 0; i < answerKeyLength; ++i)
		{
			if (answerKey[i].isMultiple)
				std::cout << answerKey[i].multiple << std::endl;
		}
	}

}//printAnswer

char* TokenizeString(std::string string , int *tokenCount)
{
	// Will cut the given string into an array of characters with just Capital letters
	// Accepts input strings of A,B,C,D   -- does not check if different capitals
	// returns: NULL if any char other than a captial letter or 'n'
	// side effect :changes tokenCount to the number of capital letters in final output a 
	int capitalCounter = 0;
	char* tokens = (char*)malloc(string.length() + 1);
	unsigned int commaCounter = 0;
	if (tokens == NULL) {
		return NULL;
	}
	for (int i = 0; i < string.length() / sizeof(char); i++)
	{
		if (string[i] >= 'A' && string[i] <= 'Z') // if it is a capital letter
		{
			tokens[capitalCounter] = string[i];
			++capitalCounter;
			continue;
		}
		else if (string[i] == ',') //if character is a ','
		{
			commaCounter++; 
			if (capitalCounter == 0) // if a comma is the first character fail
				return NULL;
			if (commaCounter % capitalCounter != 0) // if there are more commas than capitals fail
			{										// stops A,,B
				free(tokens);
				return NULL;
			}
		}
		else if (string[i] != ',') // if the character is not a capital OR comma Fail
		{
			free(tokens);
			return NULL;
		}
	}
	if (commaCounter == capitalCounter)	// Cannot end with comma
		return NULL;

	tokens[capitalCounter] = '\0'; // no clue honestly
	*tokenCount = capitalCounter;
	return tokens;
}//tokenize String

bool CheckAnswer(int answer, int multiplesTotal, IntAndBool* answerKey)
{
	// this function needs to be optimized and pruned
	// returns true if answer is correct, false if wrong, no side effects

	int multiplesCount = 0;
	const int ktotalOptions = multiplesTotal + 1;
	const int knoneOfOptionValue = ktotalOptions;
	const int kmultipleOptionValue = ktotalOptions - 1;

	for (int i = 0; i < multiplesTotal; ++i)
	{
		if (answerKey[i].isMultiple)
			++multiplesCount;
	}// count the number of multiples that are true

	if (answer == knoneOfOptionValue) // if they selected none of them are corect
	{
		if (multiplesCount == 0)
		{
			toConsole("congrats! thats correct");
			return true;
		}
		else
		{
			toConsole("that is incorrect");
			PrintAnswer(answerKey, multiplesCount, multiplesTotal);
			return false;
		}
	}
	else if (answer == kmultipleOptionValue) // if they selected multiple are correct
	{
		if (multiplesCount <= 1)
		{
			toConsole("that is incorrect");
			PrintAnswer(answerKey, multiplesCount, multiplesTotal);
			return false;
		}

		std::string input;
		int tokenCount = 0;
		char* tokenizedInput;
		toConsole("There are multiple, which options are true? (answer in form A,B,C no spaces)");
		do
		{	//Takes User input string, then converts that into a array of all the capital letters in that string
			//Only accepts formatting that is captialLetter or ',' any other char errors
			//Also keeps track of number of captial letters recieved for future use
			std::getline(std::cin, input);
			tokenizedInput = TokenizeString(input, &tokenCount); 
		} while (tokenizedInput == NULL);

		//for (int i = 0; i < tokenCount; ++i)  //Debug Printer of tokenized String
		//	toConsole(tokenizedInput[i]);

		if (tokenCount != multiplesCount) // if # of correct answers is not number of answers given
		{
			toConsole("that is incorrect");
			PrintAnswer(answerKey, multiplesCount, multiplesTotal);
			return false;
		}

		int currentOption;
		for (int i = 0; i < tokenCount; ++i)
		{
			currentOption = (int)(tokenizedInput[i] - 'A'); //A=0 , B=1, C=2..
			if (currentOption > multiplesTotal || answerKey[currentOption].isMultiple == false)
			{    // Selected option is larger than all normal options Or selected option is not correct
				toConsole("that is incorrect");
				PrintAnswer(answerKey, multiplesCount, multiplesTotal);
				return false;
			}//if more than total multiples

		}//loops tokenized input for all tokens I have

		// if above for loop found the anser was wrong, the function would have returned false
		toConsole("congrats! thats correct");
		free(tokenizedInput);
		return true;
	}//multiple option if
	else // for one answer
	{
		if ( (multiplesCount != 1) || !answerKey[answer].isMultiple ) // if number of right answers is not 1
		{
			toConsole("that is incorrect");
			PrintAnswer(answerKey, multiplesCount, multiplesTotal);
			return false;
		}
		if (answerKey[answer].isMultiple) // if that numer is correct
		{
			toConsole("congrats! thats correct");
			return true;
		}
	}
}//CheckAnswer

int MainGameLoop(GameParameter parameters) // the main game loop.
{
	//returns 0

	int currentScore = 0, currentRoll = 0;
	int intUserInput;
	char rawUserInput;
	bool notWon = true;
    bool badAnswer = false;
	IntAndBool* multiplesParrallelArray = CreateParrallelBooleanArray(parameters);
	const int ktotalOptions = parameters.multiplesCount + 1;


	//intro, with explanation and changing on parameters given.
	PrintIntroSequence(parameters);

	//Roll number game loop
	while (notWon)
	{
		currentRoll = GetRandomNumber(parameters.minRoll, parameters.maxRoll); // gets the number user is comparing

		CheckMultiples(currentRoll, multiplesParrallelArray, parameters.multiplesCount);

		std::cout << "Your score: " << currentScore << std::endl;
		std::cout << "    You rolled a " << currentRoll << std::endl;
		PrintGameOptions(parameters);
		do
		{ // get a proper answer
			rawUserInput = toupper(GetMeChar());
			intUserInput = (int)(rawUserInput - 'A'); // zeros the input

			if ((rawUserInput <= 'A' && rawUserInput >= 'Z') || (intUserInput > ktotalOptions))
			{
				badAnswer = true;
				toConsole("Please input a matching character to one of the options");
			}
		} while (badAnswer);

		if (CheckAnswer(intUserInput, parameters.multiplesCount, multiplesParrallelArray))
			++currentScore;
		else
			--currentScore;

		std::cout << std::endl << "--------------------" << std::endl;
	
		if (currentScore >= parameters.winningScore)
			notWon = false;
	}// Game Loop

	free(multiplesParrallelArray);
    return 0;
}//main game loop

bool OutroSequence()
{
	//returns true if the player wants to play again
	//prints the outro sequence as side effect
	toConsole("congratulations you've won the math game");
	toConsole("Would you like to play again? (y/n)");
	char input = GetMeYesNo();

	if (input == 'y')
		return true;
	else if (input == 'n')
	{
		toConsole("Goodbye");
		return false;
	}

	return false; // failsafe
}//Outro

GameParameter GetParameters()
{
	//Prompts user 

	char userResponse;
	bool changeParameters = false;
	// All the standard values specified, could make macro or function for this, but this is simple enough
	int minRoll = 1;
	int maxRoll = 20;
	int winningScore = 10;
	int totalMultiples = 2;
	int* allMultiples = (int*)calloc(totalMultiples, sizeof(int)); //Probably a better option
	allMultiples[0] = 2;		// using vectors would make this, and a lot easier.
	allMultiples[1] = 3;		// but im using this project to learn memory allocation and stuff

	//prompt user if they want to change from default.
	std::cout << ("Would you like to use default parameters? (y/n) ") << std::endl;
	userResponse = GetMeYesNo();

	//Check user response
	if (userResponse == 'y')  
		changeParameters = false;
	else if (userResponse == 'n')
		changeParameters = true;

	while (changeParameters)
	{
		//prompt for what to change
		std::cout << "Select what you want to change:" << std::endl 
				  << "A : Minimum roll,            (currently:" << minRoll << ')' << std::endl
				  << "B : Maximum roll             (currently:" << maxRoll << ')' << std::endl
				  << "C : Winning score            (currently:" << winningScore << ')' << std::endl
				  << "D : The multiples to check   (currently:";
					for (int i = 0; i < totalMultiples; ++i)
					{
						if (i > 0)
							std::cout << ',';
						std::cout << allMultiples[i];
					}
		std::cout << ')' << std::endl
				  << "any other character to stop" << std::endl;

		//get user response
		userResponse = toupper(GetMeChar()); // converts char to uppercase IF possible, otherwise nothing.
		switch (userResponse) // simple switch case that lets you change the four
		{					// standard parameters
			case 'A': // min roll
			{
				toConsole("What would you like to change the minimum roll to?");
				minRoll = GetMeInteger();
				break;
			}
			case 'B': // max roll
			{
				toConsole("What would you like to change the maximum roll to?");
				maxRoll = GetMeInteger();
				break;
			}
			case 'C': // winning value
			{
				toConsole("What would you like to change the winning score to?");
				winningScore = GetMeInteger();
				break;
			}
			case 'D': // Number of multiples
			{	
				//Very long case, could use function for less nesting and more readability.
				toConsole("how many different number do you want to compare the rolled number to?");

				do // Cant use a number that would make the future case options exceed the number of captial letters in english.
				{
					totalMultiples = GetMeInteger();
					if (totalMultiples > (int)('Z' - ('A' + specialSlotsCount)) + 1)
						toConsole("Hey, sorry, you can only use 24 or less comparitors");
				} while (totalMultiples > (int)('Z' - ('A' + specialSlotsCount)) + 1); // this also forces totalMUltiples to be 1-24

				// re allocate the memory for the array equal to number of elements user specified
				int* newMultiples = (int*)realloc(allMultiples, totalMultiples * sizeof(int));
				if (newMultiples != NULL)
					allMultiples = newMultiples;
				else
				{
					free(allMultiples); // if null pointer returned, breaks function and clears memory
					toConsole("memory allocation failure, quitting program");
					exit;
				}

				//Fills the array, prompting the user for each input
				for (int i = 0; i < totalMultiples; ++i)
				{
					std::cout << "multiple #" << i + 1 << " = ?";
					allMultiples[i] = GetMeInteger();
				}
				toConsole("thank you"); // be nice
				break;
			}
			default: 
			{

				changeParameters = false; break;
			}
				
		}// user response switch

		std::cout << std::endl;
	}//while changing parameters

	GameParameter parameters = { minRoll , maxRoll, winningScore , totalMultiples, allMultiples };
	return parameters;
}// Get Parameters

int main()
{
	bool keepPlaying = true;
	GameParameter parameters;
	srand(time(0)); // seed RNG in main so it never repeats by accident

	while (keepPlaying)
	{
		system("cls"); // clears the console to make it look nice
		parameters = GetParameters(); // sets the game parameters, asking if user wants to change them.
		MainGameLoop(parameters); // runs the game based on parameters
		free(parameters.multiplesArray); // frees memory incase
		keepPlaying = OutroSequence(); // prompts user to play again, and says goodbye
	}

    return 0;
}//main end