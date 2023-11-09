#include <iostream>

// blueprint for a function
template <typename type>
type Square(type val)
{
	return val * val;
}





int main()
{
	int myNumber = 5;

	std::cout << "val: " << Square(myNumber) << '\n';
	return 0;
}