#include <iostream>
#include <vector>
#include <string.h>
#include <cstring>
#include "Header.h"

// Function to create and fill a vector of MyStruct
std::vector<MyStruct> createAndFillVector() {
	std::vector<MyStruct> myVector;

	// Add elements to myVector
	MyStruct s1;
	s1.myInt = 42;
	s1.myCharPointer = new char[strlen("Hello") + 1];
	strcpy_s(s1.myCharPointer, 6, "Hello");
	myVector.push_back(s1);

	MyStruct s2;
	s2.myInt = 23;
	s2.myCharPointer = new char[strlen("World") + 1];
	strcpy_s(s2.myCharPointer, 6, "World");
	myVector.push_back(s2);

	return myVector;
}