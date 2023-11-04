#include <iostream>
#include <string>

int main()
{
	// 'primative' variable declaration

	int variable = 25; // Finds a block of memory, the size of an int, and assigns it for use with this program
						// Then fills that block of memory with the binary value equal to 25 (I think it would be 11001)
						// The adress of this variable is the number of piece of memory used,
						// but since we cant know that exact block of memories name
						// we instead just write 'variable'
						// so 'variable' IS the adress
						// lets imagine the adress is the number A04

	int poop = variable;// Much like above, this would allocate a chunk of memory the size of an int. Lets imagine this chunks adress is b08
						// then it will set that chunk in memory to be equal to what is in the chunk of memory named 'variable
						// the computer creates cunk of memory at b08, that chunk is a collection of bytes. it then looks the bytes in A04 and sets the bytes in b08 to be the same.


	int& foo = variable;// This creates a new name FOR THE SAME variable, it makes both variables share a adress,
						// this is not a new chunk of memory, like how when the program compiles and replaces all instances of 'variable' with A04
						// it will now also replace all instances of the word 'foo' with A04
						// thus a change to one variable changes both, since they are always THE SAME VARIABLE.

	++variable; 					// Since foo and variable share the same adress
	std::cout << foo << std::endl; // will output 26, since variable + 1 is 26 which is the same variable as foo
	std::cout << poop << std::endl; // will output 25, since poop is its own piece of memory and is no longer linked with 'variable'

	std::cout << std::endl;

	//Pointers

	// A pointer is a variable that holds the adress of a different piece of memory
	int* ptest; // in this case, int* means that this variable is looking for an adress for something the size of an int
				// just like the variable above, this will find and allocate a chunk of memory that is the size of an int pointer.
				// the pointer itself has its own adress like any other variable.

	//& is how to 'reference' a variable, get the adress of the variable.
	ptest = &variable; // Just like setting variable to 25, this sets ptest to the adress of variable.
					// much like a variable, the adress being pointed to can be changed easily as shown above.
					// the pointer 'ptest is now pointing to the adress of 'variable'
	std::cout << ptest << std::endl; // will print the adress that is stored in ptest, in this case the adress of 'variable'
	std::cout << &ptest << std::endl; // will print the adress of the pointer itself.
	std::cout << *ptest << std::endl; // the * used outside of declaration means 'value pointed to by', also known as dereferencing
									// so this above line will print the value pointed to by ptest,
									// in this case, the value pointed to by the adress of variable, 25.
	
	std::cout << std::endl;

	//importantly, pointers can point at any adress in memory, even other pointers
	int** ppointerPtr = &ptest; // the use of ** means a double pointer, a pointer to a pointer.
								// then set this pointer to hold the adress of the original pointer
	std::cout << ppointerPtr << std::endl; // so if we call this pointer it will return the adress of ptest
	std::cout << &ppointerPtr << std::endl; // using & will still simply return the adress of ppointerptr
	std::cout << *ppointerPtr << std::endl; // this will derefrence ppointerptr once, so 'the value pointed to by' ppointerPtr, in this case that would be the adress held by ptest A05
	std::cout << **ppointerPtr << std::endl; // this will double derefrence ppointerpt, so 'The value pointed to by (the value pointed to by ppointerPtr)'
											// or easier to think, since the value pointed to by ppointerPTr is ptest 'the value pointed to by ptest' also known as 25
				// you could also think of 'the value pointed to by' as 'what is at the adress held by'
				// so for *ptest, 'what is at the adress held by ptest' - 25
				// and for **ppointerptr, ' What is at the adress held by (what is at the adress held by ppointrptr)' -- idk this is even more strange to think about, but () help
											

	/*
		variable -> is the word written when coding to refer to whats in this block of memory,
					 when compiled it basically replaces every instance of the word 'variable with the exact adress of memory used
		&variable -> would be the adress of this exact block of memory, basically allowing you to work in terms of where someting is instead of what something is. 'zooming out'
		*variable -> tells the program that 'variable' is a pointer, meaning whatever is stored at this place in memory is supposed to be an adress.
				since variable is just a normal int,
				it doesnt allow us to do this, as we need to explicitely say something is a pointer in order to use it as a pointer
				else we would be able to input any integer or data type and attempt to acess completely random pieces of memory
				or just fail to acess a random number.
	*/

	std::cout << std::endl;

	//Arrays

	int staticArray[4] = { 0 , 1 , 2 , 3 }; // this is a standard static array with 4 elements, each element the size of an int.
						// this first, creates an int pointer.
						// Then it creates 4 slots in memory the size of ints.
						// Then sets the pointer to be pointing at the first adress in the 4 slots of memory.
						// The compiler NEEDS to know the size of the array at buildtime in c++ else it will not build
	int *dyanmicArray; // this is a simple int pointer.
					// this can be turned into an array just like above
					// To do so, we need to manually allocate the memory to be used
					// malloc (memory allocate) creates a single block of memory of set size.
					// calloc (contiguous allocation) creates multiple blocks of memory of specified size. 
					//	then returns a pointer to the first block in the chain.
					// in this case, calloc would allow us to create an array at any size we want
	int arraySize = 4;// during the runtime of a program

	// I realize that much of what is below I learned from someone who really likes C and does not use c++
	// C++ has two things that make memory allocation like this much easier and safter,
	// they are the new keyword -- and vectors
	// I will make a seperate file talking about the differences between this, new, and a vectors as this file is lengthy and should talk about the idea memory in general not just arrays.

	dyanmicArray = (int*)calloc(arraySize, sizeof(int)); // is the proper syntax to create a dyamically allocated array for C , point being dont worry too much about the syntax
		// in this case a dyamic array is useless, but if you wanted arraySize to change depenedent on the program, you do this.
		// (int*) is a type cast. the function calloc normally returns a void pointer, so we must make it an int pointer.
		// if you are making an array of a different data type, replace the ints with the data type
		// calloc then creates arraySize number of blocks in memory, each the size of "sizeof(int)
		// sizeof(int) is a seperate standard function which returns the size in bytes an int requires.
	for (int i = 0; i < 4; ++i) // just to fill the array , 
		dyanmicArray[i] = i;	// 							
	/*
	you would prefferably not use < 4 in a real program
	instead you could:
		Track the size of the array somehow and put the variable that is tracking the array size there. in this case it would be arraySize.
	Or
		use the function sizeof() which returns the number of bytes allocated to a variable
		then divide the number of bytes allocated to the whole array by the number of bytes are a single element in that array
		for this example imagine if an int is four bytes
		dyanmicArray = (int*)calloc(arraySize, sizof(int)) would create arraySize blocks of memory - 4 each block being the size that an int is 4 bytes. for a total of 16 bytes
		Therefor, if you run sizeof(dyanmicArray) it wil return the total size of the array in bytes, being 16
		and then if you take the total number of bytes (16) and divide it by the size of an indiviual element, which is 4 in this case you get the number of elements
		Total Size = Size of element * Number of elements => number of elements = total size / size of element
	*/												
		

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