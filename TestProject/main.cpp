#include <iostream>
#include <chrono>
#include <ratio>

int main()
{
	constexpr double kMilisecondPerSecond = 1000;
	constexpr double kNanosecondPerMilisecond = 1000 * 1000;	

	std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
	// takes the time since the clocks epoch, which is just some arbitrary number?

	std::chrono::duration<double, std::milli> elapsed_miliseconds;
	std::chrono::duration<double> elapsed_seconds;


	std::chrono::time_point<std::chrono::steady_clock> currentTime; 

	for (;;)
	{
		currentTime = std::chrono::steady_clock::now();
		elapsed_miliseconds = (currentTime - startTime); // this somehow automatically converts the currentTime - startTime, which is in nanoseconds, to miliseconds
															// this is probably exactly what a duration object is used for. since the standard
		if (elapsed_miliseconds.count() > kMilisecondPerSecond * 2)
		{
			break;
		}
	}
	elapsed_seconds = (currentTime - startTime);

	std::cout << elapsed_seconds.count() << " - seconds\n";
	std::cout << elapsed_miliseconds.count() << " - miliseconds\n";

	return 0;
}