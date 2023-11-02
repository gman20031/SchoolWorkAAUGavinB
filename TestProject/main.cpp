#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>      // For std::out_of_range
using namespace std;

int main() {
	vector<string> names = { "Ryley", "Edan", "Reagan", "Henry", "Caius", "Jane", "Guto", "Sonya", "Tyrese", "Johnny" };
	int index;
	string output;

	cin >> index;

	try
	{
		cout << names.at(index) << endl;
	}
	catch (out_of_range& error)
	{
		cout << "Exception! " << error.what() << endl;
		if (index < 0)
			cout << "The closest name is: " << names.at(0) << endl;
		if (index > 9)
			cout << "The closest name is: " << names.at(9) << endl;
	}

	return 0;
}
