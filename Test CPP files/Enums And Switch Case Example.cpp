#include <iostream>
#include <string>



int TestFunctionOne()
{
	std::cout << "\nTestFunctionOne achieved\n \n";

	return 0;
}//Test One end

int TestFunctionTwo()
{
	std::cout << "\n TestFunctionTwo achieved \n \n";

	return 0;
}//Test Two end

int GetMeInt(int *pinputVariable) // Does the same as the float function but grabs integers for the modulo stuff specifically.
{
	int inputInteger; // this is all the same as above

	std::cin >> inputInteger;

	while (!std::cin.good())
	{
		std::cout << "Please enter an integer \n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> inputInteger;
	}//test for ints

	*pinputVariable = inputInteger;

	return 0;
}//GetMeTwoInts func

int main()
{
	enum functionSwapper // enum of functions able to be called
	{
		TestOne = 1,
		TestTwo = 2
	};
	int selectorInt = -1;
	bool keepRunning = true; // bool to check if code should continue running.

	while(keepRunning) //allows for functions to return here after done
	{
		selectorInt = -1;

		std::cout << "select a function: \n"		// outputs possible functions to run, keeping on different lines to make easy reading.
				  << "  Test function One : 1 \n"
				  << "  Test function Two : 2 \n"
				  << "  Quit program      : 0 \n";  // use spaces to maintain continuety, since visual studio loves automatically replacing/adding stuff, making it harder to know wtf is happening.

		while(selectorInt < 0 || selectorInt > 2)   //repeats getting a int until a usable number is found.	 I would preffer to replace the 2 with something that finds the max value of the enum.
		{
			GetMeInt(&selectorInt);					// will ask for integer if user inputs wrong data type
			if (selectorInt < 0 || selectorInt > 2) std::cout << "input not valid\n"; // will return 'input not valid' if not 0-2
		}//end get int loop	
		
		if (selectorInt == 0) keepRunning = false;  // This is the check to see if the program should shut down, will only do it if the user inputs EXACTLY 0

		switch (selectorInt) {
			case functionSwapper::TestOne:TestFunctionOne(); break;		// AFAIK switch() case works as, IF Xistrue : perform y; perform z; and will continue running code until a break; is hit.
																		/*		the functionSwapper::TestOne is confusing because of the :: and the : in the sameline, but functionSwapper::TestOne is effecively just
																			a complicated way to say a variable.  	functionSwapper:: just meaning its within the enum functionSwapper, then TestOne saying the actual
																			part I am talking about.

																				It seems the best way to use switch() case; is in the following syntax 
																								case switchVariable: function(); break;
																				however
																								case switchVariable:{body  break;} -- end the body with break; much like a function ends with return;
																				also works.		
																		*/
			case functionSwapper::TestTwo:TestFunctionTwo(); break;
			case 0: std::cout << "goodbye\n"; break;
		}//function swap switch / case

	}//keep Running

	return 0;
}//main