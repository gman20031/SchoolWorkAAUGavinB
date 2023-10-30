#include <iostream>
#include <string>

struct teststruct
{
    int *array; // add the  * to denote its an array
	int minimum;
    int maximum;
};

int PrintTestStruct(teststruct printedStruct)
{
    std::cout << printedStruct::array << std::endl
    std::cout << printedStruct::minimum << std::endl
    std::cout << printedStruct::maximum << std::endl

    return 0;
}

int main()
{
	teststruct mystruct = { {2,3} , 5 , 10};

    PrintTestStruct(mystruct);

	return 0;
}//main