#include <iostream>
#include <array>

class myAss {
public:
	int *foo = nullptr;
	int bar[3]{ 1,2,3 };

	static void printArr(int * array) {
		for (int i = 0; i < 3; ++i) {
			std::cout << array[i] << ' ';
		}
		std::cout << std::endl;
	}
};

int main() {
	myAss objectOne;
	objectOne.bar[1] = 4;
	objectOne.foo = (int*)malloc(sizeof(int) * 3);
	objectOne.foo[0] = 1;
	objectOne.foo[1] = 2;
	objectOne.foo[2] = 3;

	myAss objectTwo = objectOne;
	objectTwo.bar[2] = 4;
	objectTwo.foo[2] = 4;

	myAss::printArr(objectOne.bar);
	myAss::printArr(objectTwo.bar);
	myAss::printArr(objectOne.foo);
	myAss::printArr(objectTwo.foo);


}