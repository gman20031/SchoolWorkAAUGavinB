#include <iostream>

// In original C, the use of static for both functions and variables has a simple use
// in addition to the simple use of static variables outlined in a different example file
// static functions and variables are both unable to be called from outside of the same file
// therefor if there is any capablility of someone gaining acess to your function while being in a different file
// they would be unable to use that function
// this is hard to make an example of, and to my current understanding is slightly redundant with the use of header files.

// in C++ comes member functions and variables, which have different meanings to the normal static version
class myClass {
public:
	int m_integer;
	static int m_staticInteger;

	void IntegerDoubleAdd(int input);
	static void IntegerDoubleAdd(int input);

};

int main()
{
	


}