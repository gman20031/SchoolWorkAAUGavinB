#include <iostream>
#include <chrono>

long fibonacci(unsigned n)
{
	std::cout << n << std::endl;
	if (n < 2) return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
	for(;;)
	{
		int input;
		std::cin >> input;
		std::cout << "f(x) = " << fibonacci(input) << '\n';
	}
	
	return 0;
	//std::chrono::milliseconds mil(1000);
	//mil = mil * 60;

	//for (;;)
	//{
	//	if()
	//}
}