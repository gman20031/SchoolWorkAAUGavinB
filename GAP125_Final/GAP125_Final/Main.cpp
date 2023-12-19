#include <iostream>
#include <string>
#include <time.h>
using namespace std;

#pragma region Directions & Advice

/*
DIRECTIONS:
Complete as many of the tasks below as you can.
Nothing you write in main will be counted; use it as your scratch paper for testing things.

Here’s some advice:
- Read all tasks first. Immediately answer any that you think will be quick and easy.
- Complete at least 1, 3, 4, 5, 6, and either 9 or 10. Complete the others if you have time.
- Focus on getting the right answer. Only worry about commenting and the coding standard if you are instructed to, or if you have extra time.
- Do not consider your answer complete until you have tested it.
- Figuring out the questions is not part of the exam. If you don’t understand what you’re being asked to do, raise your hand.
- When given function specifications, you must follow them PRECISELY. For example, do not add side effects or return values that aren't requested.
	- The exception: parameters may be added as a form of output!
- Remember that you can use the internet and any other resources you have, with the following exceptions:
  - Don’t talk to anyone.
  - Don’t copy exact solutions from the internet.
- Don’t forget to breathe, drink water, and take your time. Don’t panic.
- Use the + and - buttons to the left to expose and hide things as you work on them.
*/

#pragma endregion

#pragma region Task 1

/*
TASK 1
Write a function to play with randomizing float numbers:
- Parameters : none
- Side effects :
  - Allocate a float array with a size of 5 and assign each element as follows :
  - Generate 2 random numbers
  - Divide one by the other and assign it to the element as a float
  - Be sure to avoid rounding to whole numbers
  - Then print each element in reverse order
- Return : nothing
- Example:
  - examples of random numbers are 3/10, 13/11, 14/2
  - each above expression can and should be stored as a fractional number, i.e. .3333, 1.1818, 7
  - they would be printed backwards, so in this case 7, 1.1818, .3333
*/

// Put your solution to #1 here.
// 5 elements, each element equals Random1 / random2, 
void PrintRandomFloatArray()
{
	//srand((time_t)time(0)); -- seeded in main now to allow to run multiple times
	
	std::cout << "Task One:" << std::endl;
	float topNumber, bottomNumber;
	constexpr int arraySize = 5;
	float floatArray[arraySize]{};
	for (int i = 0; i < arraySize; ++i)
	{
		topNumber = (float)rand();
		bottomNumber = (float)rand();
		floatArray[i] = topNumber / bottomNumber;
	}
	for(int i = 0 ; i < arraySize ; ++i)
	{
		std::cout << floatArray[arraySize - (i + 1)] << std::endl;
	}
}


#pragma endregion

#pragma region Task 2

/*
TASK 2
Write a function that generates N random numbers, then returns the highest and lowest ones. Follow these specifications as closely as possible :
Parameters:
	min: an integer
	max : an integer
	numRolls : an integer
Side effects :
	Generate numRolls random numbers in the range[min, max] (this range is inclusive, so both min and max should be possible values)
	Determine which was the lowest and which was the highest
Returns :
	Both the highest and lowest number 
*/

// Put your solution to #2 here.
// a number of rolls between stated values.

struct HighestLowest
{
	int m_highest = -1;
	int m_lowest = -1;
};

HighestLowest GetHighLowFrom(int min, int max, int numRolls)
{
	//srand((time_t)time(0)); -- seeded in main now to allow to run multiple times
	if(numRolls <= 0)
		return {-1,-1}; // dont run if num rolls is 0 or less

	int lowest = 0; 
	int highest = 0;
	
	lowest = min + rand() % (max - min + 1); // first roll

	if (numRolls == 1)
		return {lowest,lowest}; //should be the only edge case of a single roll.


	int newRoll = min + rand() % (max - min + 1); // second roll.
	if(newRoll >= lowest)
		int highest = newRoll;
	else
	{
		highest = lowest;
		lowest = newRoll;
	}
	
	for (int i = 0; i < numRolls - 2; ++i) // 3rd + roll
	{
		newRoll = min + rand() % (max - min + 1);
		if(newRoll > highest)
			highest = newRoll;
		if(newRoll < lowest)
			lowest = newRoll;
	}
	
	HighestLowest output = {highest,lowest};

	return output;
}

#pragma endregion

#pragma region Task 3

/*
TASK 3
Write a function called GenerateArray() that meets these specifications
- Purpose: generate an array of random numbers and return it.
- Parameters: two numbers n and m
- Side effects:
  - Generate an array of numbers with (a random size between n and m) + 1
  - Fill the array with random numbers between n and m
  - Fill the last element with the value zero
- Return: the generated array
- Example:
  - 3 and 6 are passed in
  - a number from the range [3,6] is pulled. Let's say it's 4.
  - an array with a size of 4 + 1 = 5 is generated
  - 4 more numbers from the range [3,6] are pulled and put int the array
  - 0 is assigned to the last element
  - the array is returned from the function.
*/


// Put your solution to #3 here.
double* GenerateArray(int n, int m)
{
	//srand((time_t)time(0)); -- seeded in main now to allow to run multiple times

	int arraySize = (n + rand() % (m - n + 1)) + 1;
	double* pNumberArray = new double[arraySize];

	for (int i = 0; i < arraySize-1; ++i)
	{
		pNumberArray[i] = n + rand() % (m - n + 1);
	}
	pNumberArray[arraySize-1] = 0;

	return pNumberArray;
}


#pragma endregion

#pragma region Task 4

/*
TASK 4
Demonstrate the usage of the function you wrote in #3 by performing these steps in a new function:
- Write a loop that does the following 5 times:
  - Call GenerateArray(), passing 4 and 8 as arguments.
  - Use a loop to print all of the contents of the generated array; stop before printing the zero.
  - Perform any necessary cleanup of the output of GenerateArray().

*/

void TestTask3()
{
	double* pOutput;
	for (int i = 0; i < 5; ++i)
	{	
		std::cout << "Loop number " << i+1 << '\n';
		pOutput = GenerateArray(4,8);

		for (double* pIterator = pOutput; *pIterator != 0; ++pIterator)
		{
			std::cout << *pIterator << '\n';
		}

		std::cout << '\n';
		delete pOutput;
	}
}

#pragma endregion

#pragma region Task 5

/*
TASK 5
Using best practices, define a data type called Player with the following members:
- the player’s username
- the player’s friend list (they may have up to 255 friends; each friend is another Player)
- a SetFriend function:
	- Inputs:
		- friend: another player
		- n: an integer
	- Side effects:
		- Stores the address of friend in the nth element of the friend list
	- Example:
		- player1.SetFriend(player2, 0)
		- player1 now stores the address of player2 at index 0 of its friend list

*/

// Put your solution to task 5 here.


class Player
{
private:
	const char* m_username;
	Player* m_pFriendArray[255]{};

public:
	Player(const char* username) : m_username(username){};

	const char* GetUsername(){return m_username;};

	void SetFriend(Player* friendPointer, int index)
	{
		m_pFriendArray[index] = friendPointer;
	}
};



#pragma endregion

#pragma region Task 6

/*
TASK 6
Demonstrate you know how to work with objects by doing the following:
- allocate two Player objects:
	- player 1 should be named “Neo”
	- player 2 should be named “Trinity”
	- player 3 should be named “Morpheus”
	- Set Neo’s 0th friend to Trinity and 1st friend to Morpheus
	- Set Trinity’s 1st friend to Morpheus and 3rd friend to Neo
	- Set Morpheus’ 253th friend to Trinity and 254th friend to Neo

*/

void TestTask5()
{
	Player playerNeo("Neo");
	Player playerTrinity("Trinity");
	Player playerMorpheus("Morpheus");

	playerNeo.SetFriend(&playerTrinity,0);
	playerNeo.SetFriend(&playerMorpheus,1);

	playerTrinity.SetFriend(&playerMorpheus,1);
	playerTrinity.SetFriend(&playerNeo,3);
	
	playerMorpheus.SetFriend(&playerTrinity,253);
	playerMorpheus.SetFriend(&playerNeo,254);
}

#pragma endregion

#pragma region Task 7

/*
TASK 7

Write a new data type called PremiumPlayer that has everything Player has but add these members.
You can copy and paste some contents of Player to start this.
- the player’s premium currency wallet (integer; the amount of money they have earned in the game)
- a ModifyWallet function that can be used to increase or decrease this player’s wallet by n
	- Examples: player.ModifyWallet(100) to gain $100, or player.ModifyWallet(-100) to lose $100
- a GiftCurrency function that can be used to gift money to another user on the player's friends list
	- Example: player.GiftCurrency(20, 0) will give $20 to the 0th friend on their friends list


*/

class PremiumPlayer
{
private:
	int m_wallet = 0;
	const char* m_username;
	PremiumPlayer* m_pFriendArray[255]{};

public:
	PremiumPlayer(const char* username) : m_username(username) {};

	const char* GetUsername() { return m_username; };

	void SetFriend(PremiumPlayer* friendPointer, int index)
	{
		m_pFriendArray[index] = friendPointer;
	}

	void ModifyWallet(int currencyChange)
	{
		m_wallet += currencyChange;
	}

	void GiftCurrency(int giftedAmount, int friendIndex)
	{
		if(giftedAmount > m_wallet)
		{
			std::cout << "not eough money to gift currency\n";
			return;
		}
		if (m_pFriendArray[friendIndex] == nullptr)
		{
			std::cout << "No friend at that index\n";
			return;
		}

		m_pFriendArray[friendIndex]->ModifyWallet(giftedAmount);
		ModifyWallet(-giftedAmount);
	}

};
// Put your solution to task 7 here.


#pragma endregion

#pragma region Task 8

/*
TASK 8

Replicate your answer to #6 except for these changes:
- Use PremiumPlayer instead of Player
- After setting up the PremiumPlayers as in #6:
	- give Morpheus $1000
	- have Morpheus give $200 to Neo using the GiftCurrency function.

*/

void TestTask7()
{
	PremiumPlayer playerNeo("Neo");
	PremiumPlayer playerTrinity("Trinity");
	PremiumPlayer playerMorpheus("Morpheus");

	playerNeo.SetFriend(&playerTrinity, 0);
	playerNeo.SetFriend(&playerMorpheus, 1);

	playerTrinity.SetFriend(&playerMorpheus, 1);
	playerTrinity.SetFriend(&playerNeo, 3);

	playerMorpheus.SetFriend(&playerTrinity, 253);
	playerMorpheus.SetFriend(&playerNeo, 254);


	playerMorpheus.ModifyWallet(1000);
	playerMorpheus.GiftCurrency(200,254);
}


#pragma endregion

#pragma region Task 9

/*
TASK 9
This function is deliberately left un-commented, and has one or more errors. Do the following:
- Find out what the error or errors are.
	- Write a comment explaining all the methods or tools that you can use to test and locate the problem.
- Investigate what is causing the error or errors.
	- Write a comment explaining all of the methods or tools that you can use to investigate.
- Fix the error or errors
	- Write a comment explaining all of the methods or tools that you can use to fix the error, including alternative solutions if any.
If you see any other improvements you can make, feel free to do so, but leave an additional comment explaining what you did and why.
*/

////////////////////////////////////////////////////////////////////////////////////
// ToLower: Uses a mathematical property of the ASCII table to convert all capital
// letters to their lowercase counterparts. Other characters should not be affected.
//
// Example: "Hello, World!" becomes "hello, world!"
//
// Parameters: aString: any string.
// Returns: the modified string.
////////////////////////////////////////////////////////////////////////////////////

//this is being left uncommented to showcase the old code, I also rennamed it to ensure
string OldToLower(string aString) 
{
	// The trick is that all uppercase letters are in the range between 65 ('A')
	// and 90 ('Z') and that you can add 32 ('a' - 'A') to any uppercase
	// letter to get its lowercase version. (e.g. 'Z' + 32 = 'z')

	constexpr char kFirstCapitalAsciiChar = 'A';
	constexpr char kLastCapitalAsciiChar = 'Z';
	constexpr int kDiffBetweenCapitalAndLowercase = ('a' - 'A');

	for (size_t i = 0; i < aString.size(); ++i)
	{
		char currentChar = aString.at(i);
		if (currentChar >= kFirstCapitalAsciiChar
			&& currentChar <= kLastCapitalAsciiChar)
		{
			currentChar += kDiffBetweenCapitalAndLowercase;
		}
	}

	return aString;
}
/*
// Explain how to test and find the error here.

	first thing to do would be run the function with different inputs
	I will sent the argument "Hello, WoRld!" to see what it takes in, it should read this in as a string and convert to "hello, world!"
	This will result in the actual output of "Hello, WoRld!", meaning that the function did not change the input at all.
	This can be done with many different inputs to dial into what might be the specific issue.

// Explain how to investigate the cause of the error here.
	The simpilest thing to do would be go step by step throug the function in the debugger
	Setup a wathch list of every variable in the function to ensure you know what they are doign at every step of the function
	in this function, variables to watch are.
	
		kFirstCapitalAsciiChar			- this should be 'A' or 65
		kLastCapitalAsciiChar			- this should be 'Z' or 90
		kDiffBetweenCapitalAndLowercase - this should be 32 and notated by the comments
+		aString							- this should be the string we inputted
		i								- this helps track which letter in the string we are on
		currentChar						- this should tell you which letter is currently being looked at, also showing us the error in the function.
	
	Then stepping through you will notice that i and currentChar change, but nothing else in the function does.
	Also, at the end of the function we simply return the exact string taken as input. 
	This indicates that the for loop is changing anything about the string, and we also do not export a differnt string than the input.
	Which given this function is meant to return a string, we need to make a second string.


// Explain how to fix the error including alternatives here.
	things to change
		preffer to pass string by reference
		delcaring variables within a for loop
		return a modified string.
*/

std::string ToLower(std::string& aString) // preffer to pass by reference as string is an object.
{
	// The trick is that all uppercase letters are in the range between 65 ('A')
	// and 90 ('Z') and that you can add 32 ('a' - 'A') to any uppercase
	// letter to get its lowercase version. (e.g. 'Z' + 32 = 'z')

	constexpr char kFirstCapitalAsciiChar = 'A';
	constexpr char kLastCapitalAsciiChar = 'Z';
	constexpr int kDiffBetweenCapitalAndLowercase = ('a' - 'A');

	std::string outputString = aString; // make copy of our input string, as we need to ouput something differnt.
										// we could avoid making a copy, but we do not want the side effect of changing the original given string, so we do this.
										// either way we are required to make a copy of the string at least once if we want to return a string.

	char currentChar;//this should be declared outside of the for loop, the compiler will do this for us in the old code, 
					//but i preffer to not obscure my program behind the compiler.
	for (size_t i = 0; i < aString.size(); ++i)
	{
		currentChar = aString.at(i); // we still look at the character at i
		if (currentChar >= kFirstCapitalAsciiChar 
			and currentChar <= kLastCapitalAsciiChar) // if between capital A and Z
		{
			currentChar += kDiffBetweenCapitalAndLowercase; // this will still shift the current letter to lowercase.
			outputString.at(i) = currentChar; // the main thing we needed was to override the string.
		}
	}

	return outputString;// then we need to actually return the new string.
}

#pragma endregion

#pragma region Task 10

/*
TASK 10
This function is deliberately left un-commented, and has one or more poblems. Do the following:
- Find out what the problem or problems are.
	- Write a comment explaining all the methods or tools that you can use to test and locate the problem.
- Investigate what is causing the error or errors.
	- Write a comment explaining all of the methods or tools that you can use to investigate.
- Fix the error or errors
	- Write a comment explaining all of the methods or tools that you can use to fix the error, including alternative solutions if any.
If you see any other improvements you can make, feel free to do so, but leave an additional comment explaining what you did and why.
*/

////////////////////////////////////////////////////////////////////////////////////
// EnterName: Prompts the user to enter their name. Gives them a chance to start
// over if they make a mistake.
// 
// Returns: a pointer to the entered name.
////////////////////////////////////////////////////////////////////////////////////
//old function
char* OldEnterName()
{
	constexpr int kYesResponseCount = 2;	   
	constexpr char kYesResponses[]{ 'y', 'Y' };

	cout << "Enter the length of your name: ";
	int size;
	cin >> size;

	char* pName = new char[size];
	cout << "Now enter your name (no spaces, please): ";
	cin >> pName;

	cout << "You entered: " << pName << ". Is this correct? (y for yes) ";
	char yesOrNo;
	cin >> yesOrNo;

	for (int i = 0; i < kYesResponseCount; ++i)
	{
		if (yesOrNo == kYesResponses[i])
		{
			return pName;
		}
	}

	return OldEnterName();
}



// Explain how to test and find the error here.

	// for this, we can go line by line in the function to see if there are any obvious things that may be wrong.
	// for instance, it uses recursion to find the answer, which, just feels incredibly wrong.
	// and for this program, doing so causes a memory leak.
	// then you can run the function to see if anything breaks by attempting different inputs



// Explain how to investigate the cause of the error here.
	// running the function without trying to break it, it works fine.
	// running the function but trying to break it, you realize that it still lets you write to the array beyond the size inputted.
	// Ive never used bleach or visual leak detector, but it can be used to show if ther are any leaks detected.
	// one of the biggest issues here is that the function uses reccursion, which leads to a memory leak as in every
	// stackframe it will always allocate a new array on the heap, and never deletes that array.

	// also at no point does it say the function must return a char*

// Explain how to fix the error including alternatives here.

#include <iomanip> // to allow us to control the number of characters input with cin
#include <limits>
char* EnterName()
{
	//constexpr int kYesResponseCount = 2;	       //?
	//constexpr char kYesResponses[]{ 'y', 'Y' }; // if y and Y are the only two responses these are unneccary as an array.
	// if you wish to keep  any magic characters, which these would not be in this case. you can do the following.
	constexpr char lowerYesRespone = 'y';
	constexpr char upperYesRespone = 'Y';
	bool nameFound = false;

	while(!nameFound)
	{
		cout << "Enter the length of your name: ";
		int size;
		cin >> size;

		char* pName = new char[size];
		cout << "Now enter your name (no spaces, please): ";
		//cin >> pName; // its crazy to me that this functions as intended, the more I learn about cin, the more I dislike it.
		std::cin >> std::setw(size+1) >> pName; //setw will only let a certain number of characters
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // this ensures that we dont have any weird stream buffer shenanigans.
		//its 4:32, im done, should have just useds strings, no reason to mess with allocating.

		cout << "You entered: " << pName << ". Is this correct? (y for yes) ";
		char yesOrNo;
		cin >> yesOrNo;

		if(yesOrNo == lowerYesRespone or yesOrNo == upperYesRespone)
			return pName;
		else
			delete[] pName;
	}

	//for (int i = 0; i < kYesResponseCount; ++i)
	//{
	//	if (yesOrNo == kYesResponses[i])
	//	{
	//		return pName;
	//	}
	//}  -- this all becomes irrelevant with the new constexpressions, this also adds a 'ton' of complexity

	//return EnterName(); -- dont use reccursion unless absolutely neccary.
}

#pragma endregion

int main()
{
	srand((time_t)time(0));

	char* myName = EnterName();


	system("pause");
	return 0;
}









