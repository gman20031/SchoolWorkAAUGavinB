#include <iostream>
#include <string>

int main()
{
	// 'primative' variable declaration

	int variable = 25; // Finds a block of memory, the size of an int, and assigns it for use with this program
	// Then fills that block of memory with the binary value equal to 25
	// The adress of this variable is the number of piece of memory used,
	// but since we cant know that exact block of memories name
	// we instead just write 'variable'
	// when 'variable' IS the adress
	// lets imagine the adress is the number A04
	int poop = variable;// this would then assign the variable foo to be equal to 'variable'
	// however it also finds a new block of memory to store 'poop' at, thus makig two things both equal to 25;
	int& foo = variable;// This creates a new name FOR THE SAME variable, it makes both variables share a adress,
	// thus a change to one variable changes both, since they are always the same thing.
	++variable; // Since foo and variable share the same adress
	std::cout << foo << std::endl; // will output 26, since variable + 1 is 26 and they are both the same thing.
	std::cout << poop << std::endl; // will output 25, since poop is its own piece of memory and is no longer linked with 'variable'
	//std::cout << *variable; not doable
	/*
		variable -> is the word written when coding to refer to whats in this block of memory
		&variable -> would be the number of this exact block of memory, basically zooming out when thinking of coding.
		*variable -> would be nothing, as we cant use a piece of memory as an adress.
				it doesnt allow us to do this, as we need to explicitely say something is a pointer in order to use it as a pointer
				else we would be able to input any integer or data type and attempt to acess completely random pieces of memory
				or just fail to acess a random number.
	*/

	std::cout << std::endl;

	//Pointers

	int* ptest; // A pointer is something that holds in memory the adress of a differnt piece of memory
	// in this case, int* means that this variable is looking for pieces of memory the size of ints
	ptest = &variable; // the reference 'ptest' refers to the place in memory that the pointer is.
	// much like a variable, the adress being pointed to can be changed easily as shown above.
	// the pointer 'ptest is now pointing to the adress of 'variable'
	std::cout << ptest << std::endl; // will print the adress that is stored in ptest, in this case the adress of 'variable'
	std::cout << &ptest << std::endl; // will print the adress of the pointer itself.
	std::cout << *ptest << std::endl; // the * used outside of declaration means 'value pointed to by'
	// so this above line will print the value pointed to by ptest,
	// in this case, the value pointed to by the adress of variable, 25.

	std::cout << std::endl;

	//Arrays

	int staticArray[4] = { 0 , 1 , 2 , 3 }; // this is a standard static array with 4 elements, each element the size of an int.
	// this first, creates an int pointer.
	// Then it creates 4 slots in memory the size of ints.
	// Then sets the pointer to be pointing at the first adress in the 4 slots of memory.
	// The compiler NEEDS to know the size of the array at buildtime in c++ else it will not build
	int* dyanmicArray; // this is a simple int pointer.
	// this can be turned into an array just like above
	// To do so, we need to manually allocate the memory to be used
	// malloc (memory allocate) creates a single block of memory of set size.
	// calloc (contiguous allocation) creates multiple blocks of memory of specified size. 
	//	then returns a pointer to the first block in the chain.
	// in this case, calloc would allow us to create an array at any size we want
	int arraySize = 4;// during the runtime of a program
	dyanmicArray = (int*)calloc(arraySize, sizeof(int)); // is the proper syntax to create a dyamically allocated array
	// in this case a dyamic array is useless, but if you wanted arraySize to change depenedent on the program, you do this.
	// (int*) is a type cast. the function calloc does returns a void pointer, so we must make it an int pointer.
	// if you are making an array of a different data type, replace the ints with the data type
	// calloc then creates arraySize number of blocks in memory, each the size of "sizeof(int)
	// sizeof(int) is a seperate standard function which returns the size in memory an int requires.
// Much of what arrays can do, and dynamic arrays can be replaced with vectors
// vectors are effectively the c++ way to do dynamic arrays, and the calloc and specifif memory allocation
// is mainly for C.
// #include <vector> -- research vectors.
	for (int i = 0; i < 4; ++i) // just to fill the array
		dyanmicArray[i] = i;

	//there are subtle differnces between the two arrays when using & and *, but otherwise can be used very similarly.
	std::cout << dyanmicArray << std::endl;  //returns the pointer dynamic array
	std::cout << &dyanmicArray << std::endl; //returns adress of the pointer dynamic
	std::cout << *dyanmicArray << std::endl; //returns what the pointer is pointing at
	std::cout << dyanmicArray[0] << std::endl; //returns what the pointer is pointing at with 0 change
	std::cout << "static" << std::endl;;
	std::cout << staticArray << std::endl;	//returns the adress of the first block in the array
	std::cout << &staticArray << std::endl; //returns the adress of the entire static array, which is the adress of the first block 
	std::cout << *staticArray << std::endl; //returns the first element of the array
	std::cout << staticArray[5] << std::endl; //returns the first element of the array

	return 0;
}//main