#include <vector>
#include <iostream>

/*
	to explore the uses of vectors and learn some of the basic member functions
	functions to learn:
	at()
	size()
	push_back()
	back()
	pop_back()
	resize()
	find()
*/

#define Print(str) std::cout << str << std::endl;

int main()
{
	int vectorElements = 1;
	int elementValue = 2;
	std::vector<int> myVector(vectorElements);

	Print(myVector.at(0));

}