#include <iostream>
#include <string>
#include <iomanip> 
//using namespace std;



int main()
{
	int playerCount;
	int* playerScores;

	std::cin >> playerCount;
	playerScores = (int*)calloc(playerCount + 1, sizeof(int));

	for (int i = 0; i < playerCount; ++i)
	{
		playerScores[i] = 0;
	}

	for (int i = 0; i < playerCount; ++i)
	{
		std::cout << playerScores[i];
	}

	for (int i = 0; i < playerCount; ++i)
	{
		std::cout << playerScores[i];
	}

	free(playerScores);
	return 0;
}//main
