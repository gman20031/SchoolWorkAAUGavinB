#include <limits>
#include <string>
#include <iostream>
#include <time.h>


char GetMeYesNo()// get the variable I want to change, make sure its a character
{
	char inputOne;
	bool badCharacter = true;

	while(badCharacter) // currently only way out is through break; unsure if good idea or if I should just make bad character false.
	{
		std::cin >> inputOne; //could use _getch but I know what this does, and am sure this will catch most of the bad responses.

		while (!std::cin.good()) //If one or both of the inputs were not compatiable, it will be false, and go to this while loop
		{
			std::cout << "That was not a proper response. Input a y or n nothing else \n";
			std::cin.clear();													// Resets all error flags from cin
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // effectivelly clears the cin stream buffer
			std::cin >> inputOne;
		}// while not good

		if (inputOne == 'y' || inputOne == 'n')
		{ 
			return inputOne;
			badCharacter = false; // ends loop
		}
		else std::cout << "Please input y or n only \n"; // if not y or n will restart loop
	}//bad character 
	
	return 'x'; //just incase
}//get Yes No

//does not prompt unless it fails
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

	return userIntInput;
}//getMe Int 

int main()
{
	const int kmaxDieRoll = 6;
	int roundPoints = 0;
	int dieRollValue;
	bool keepRolling = true;
	bool wonGame = false;
	//std::string currentPlayerStr = "player one"; irrelevant now im using an array

	int playerCount, currentPlayer = 0;
	int* playerScores;// for setting up player count array

	//Seed the PRNG
	srand(time(0));

	//Intro sequence
	std::cout << "hello, welcome to the dice game." << std::endl
			  << "Players switch off rolling dice. Each round the current player rolls the dice, adding its value to your round points." << std::endl
			  << "Then either continue rolling or stop, stopping adds your round points to your total score." << std::endl
			  << "If you ever get over 10 round score you forfeit your turn and lose all round points" << std::endl
			  << "First player to 50 total score wins" << std::endl
			  << std::endl
			  << "how many players would you like to play with? ";

	playerCount = GetMeInteger();
	playerScores = (int*)calloc(playerCount + 1, sizeof(int)); 
	playerScores[0] = 45; // debug
	// this should then create an array 
	// with size equal to the number of players +1
	// so when I get to the element of the exact number of players, that means its time to reset
	// and I can set current player back to 0
	// the sizeof(int) thing is basically telling it to split it up into chunks that ints can fit into.

	system("pause");

	while(!wonGame) // Game Loop -- currently only way out is through break;
	{
		keepRolling = true; // reset the rolling loo
		roundPoints = 0;	// resets the round points
		dieRollValue = 0;	// resets the current dice roll -- probably not neccesary?

		while (keepRolling) // Round Loop
		{
			char playerInput = 'x';		// initialized and resets the current player input and points -- also probably not neccasary to do this.
			int roundTotalScoreDisplay = 0;	// could be a bad idea to constantly reset and add to memory?
			

			dieRollValue = 1 + rand() % (kmaxDieRoll);	//Rolling the D6
			roundPoints += dieRollValue;

			// Sets the total score that will be displayed in the round counter to what the current players score is.
			roundTotalScoreDisplay = playerScores[currentPlayer];

			//Game window
			std::cout << std::endl
					  << "Current player : " << "Player " << currentPlayer + 1 << std::endl //remember to +1 everytime you print current player, since it starts at 0
					  << "      Total score  : " << roundTotalScoreDisplay << std::endl
					  << "      you rolled a : " << dieRollValue << std::endl
					  << "      making your total this round : " << roundPoints << std::endl;

			if(roundPoints > 10)		//checks to see if the current player over rolled
			{
				std::cout << "it looks like your total points is over 10, ending your turn :(" << std::endl;
				system("pause");
				break;
			}// if you over rolled

			std::cout << "Player " << currentPlayer + 1 << " would you like to roll again? (y/n)\n"; // ask if they want to continue round
			playerInput = GetMeYesNo();

			if(playerInput == 'n') // yes or no continue question
			{
				//std::cout<< "in n if";
				playerScores[currentPlayer] += roundPoints;
				keepRolling = false;
			}// if you want to stop
			if(playerInput == 'y') continue; // resets loop if they say yes, coninue; not needed but better for readability and expandability in my mind

		}//Round being played
	
		if (playerScores[currentPlayer] >= 50)
			break; //check for winner and breaks the game loop if they do
		
		// goto next player
		++currentPlayer;
		if (currentPlayer == playerCount)
			currentPlayer = 0;

		//output scoreboard for player information
		std::cout << std::endl
			   	  << "---------End-Round-Scoreboard---------" << std::endl;
		for (int i = 0; i < playerCount; ++i)
		{
			std::cout << "Player " << i + 1 << " score : " << playerScores[i] << std::endl; // print every player in game
		}

		std::cout << "-        Next Up " << "Player " << currentPlayer + 1 << std::endl;
		std::cout << "--------------------------------------" << std::endl;
		system("pause");
		

	}
	// Game being played
	
	std::cout << "Congratulations " << "Player " << currentPlayer+1 << " You won the game" << std::endl;
	std::cout
		<< "---------End-Game--Scoreboard---------" << std::endl;
		for (int i = 0; i < playerCount; ++i)
		{
			std::cout << "Player " << i + 1 << " score : " << playerScores[i] << std::endl; // print every player in game
		}
	std::cout << "-        Next Up " << "Player " << currentPlayer + 1 << std::endl;
	std::cout << "--------------------------------------" << std::endl;
	//Game Won -- Outro thing

	free(playerScores);
	return 0;
}//main



