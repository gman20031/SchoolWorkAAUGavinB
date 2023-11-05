#include <iostream>

#define print(str) std::cout << str << std::endl
#define flr(number) (int)number

int main() {
	constexpr double firstNumber = 30, secondNumber = 12;

	double quotent;
	int truncQuotent;
	double doubRemainder;
	int	   intRemainder;

	quotent = firstNumber / secondNumber; // first get the result of the division									EX. 30 and 12 = 2.5
											     // then get the number only equal to the area to the right of the decimal	- > 0.5
	truncQuotent = flr(quotent);				 // get truncated version of quotent										flr(2.5) -> 2.0
	doubRemainder = quotent - truncQuotent;		 // then remove the truncated version from quotent							2.5 - 2.0 = 0.5
	doubRemainder = doubRemainder * secondNumber;

	print(doubRemainder);

	system("pause");

	return 0;
}
