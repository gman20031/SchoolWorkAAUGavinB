#include <conio.h>
#include <iostream>
#include <random>
#include <time.h>

using namespace std;

// Function prototypes.
int main();
void Introduce();
void RunGameLoop();
bool ProcessTurn();
void DisplayState();
char GetUserChoice();
char GetCpuChoice();
int GetOutcome(char playerOneChoice, char playerTwoChoice);
void UpdateGameState(int outcome);
void DisplayOutcome(char playerOneChoice, char playerTwoChoice, int outcome);

// Player choice constants.
constexpr char kRock = 'r';
constexpr char kPaper = 'p';
constexpr char kScissors = 's';
constexpr int kCpuChoiceCount = 3;

// Quit command.
constexpr char kQuit = 'q';

// Outcome constants.
constexpr int kQuitOutcome = 0;
constexpr int kPlayerOneWins = 1;
constexpr int kPlayerTwoWins = 2;
constexpr int kDraw = 3;

// Score variables.
int g_playerOneScore = 0;
int g_playerTwoScore = 0;

/////////////////////////////////////////////////////////////
// Introduces the game, then starts the game loop.
/////////////////////////////////////////////////////////////
int main()
{
	Introduce();
	RunGameLoop();

	return 0;
}

/////////////////////////////////////////////////////////////
// Introduces the game.
/////////////////////////////////////////////////////////////
void Introduce()
{
	srand(time(0));

	cout << "Welcome to Rock Paper Scissors!" << endl;
	cout << "Each round, enter (r)ock, (p)aper, or (s)cissors." << endl;
	cout << "Press (q) any time to quit." << endl;
	system("pause");
}

/////////////////////////////////////////////////////////////
// Runs and manages the main game loop.
/////////////////////////////////////////////////////////////
void RunGameLoop()
{
	bool quit = false;
	while (!quit)
	{
		quit = ProcessTurn();
	}
	std::cout << "thanks for playing" << std::endl;
}

/////////////////////////////////////////////////////////////
// Processes a single turn of the game.
/////////////////////////////////////////////////////////////
bool ProcessTurn()
{
	DisplayState();
	char userChoice = GetUserChoice();
	if (userChoice == kQuit || userChoice == NULL)
		return true;
	char cpuChoice = GetCpuChoice();
	int outcome = GetOutcome(userChoice, cpuChoice);
	UpdateGameState(outcome);
	DisplayOutcome(userChoice, cpuChoice, outcome);
	return false;
}

/////////////////////////////////////////////////////////////
// Displays the current state of the game.
/////////////////////////////////////////////////////////////
void DisplayState()
{
	system("cls");
	cout << "Player One Score: " << g_playerOneScore << endl;
	cout << "Player Two Score: " << g_playerTwoScore << endl;
	cout << "(r)ock, (p)aper, (s)cissors, shoot!" << endl;
	cout << "Or press (q) to quit." << endl;
}

/////////////////////////////////////////////////////////////
// Requests a choice from the user.
/////////////////////////////////////////////////////////////
char GetUserChoice()
{
	return (char)_getwch();
}

/////////////////////////////////////////////////////////////
// Randomly selects a choice for the cpu.
/////////////////////////////////////////////////////////////
char GetCpuChoice()
{
	int randomNumber = 1 + rand() % kCpuChoiceCount;
	switch (randomNumber)
	{
	case 1:
		return kRock; break;
	case 2:
		return kPaper; break;
	case 3:
		return kScissors; break;
	default:
		return NULL; break;
	}

}

/////////////////////////////////////////////////////////////
// Determines the outcome based on the two players' choices.
/////////////////////////////////////////////////////////////
int GetOutcome(char playerOneChoice, char playerTwoChoice)
{
	int outcome;

	if (((playerOneChoice == kRock and playerTwoChoice == kScissors)
		or (playerOneChoice == kPaper and playerTwoChoice == kRock))
		or (playerOneChoice == kScissors and playerTwoChoice == kPaper))
	{
		outcome = kPlayerOneWins;
	}
	else if ((playerTwoChoice == kRock and playerOneChoice == kScissors)
		or (playerTwoChoice == kPaper and playerOneChoice == kRock)
		or (playerTwoChoice == kScissors and playerOneChoice == kPaper))
	{
		outcome = kPlayerTwoWins;
	}
	else
	{
		outcome = kDraw;
	}

	return outcome;
}

/////////////////////////////////////////////////////////////
// Updates the state of the game based on the turn's outcome.
/////////////////////////////////////////////////////////////
void UpdateGameState(int outcome)
{
	switch (outcome)
	{
	case kPlayerOneWins:
		++g_playerOneScore;
	case kPlayerTwoWins:
		++g_playerTwoScore;
	}
}

/////////////////////////////////////////////////////////////
// Displays the outcome to the user.
/////////////////////////////////////////////////////////////
void DisplayOutcome(char playerOneChoice, char playerTwoChoice, int outcome)
{
	switch (playerOneChoice)
	{
	case kRock:
		cout << "You chose rock." << endl; break;
	case kPaper:
		cout << "You chose paper." << endl; break;
	case kScissors:
		cout << "You chose scissors." << endl; break;
	}

	switch (playerTwoChoice)
	{
	case kRock:
		cout << "Your opponent chose rock." << endl; break;
	case kPaper:
		cout << "Your opponent chose paper." << endl; break;
	case kScissors:
		cout << "Your opponent chose scissors." << endl; break;
	}

	switch (outcome)
	{
	case kPlayerOneWins:
		cout << "Player one wins!" << endl; break;
	case kPlayerTwoWins:
		cout << "Player two wins!" << endl; break;
	case kDraw:
		cout << "It's a draw." << endl; break;
	}
	system("pause");
}