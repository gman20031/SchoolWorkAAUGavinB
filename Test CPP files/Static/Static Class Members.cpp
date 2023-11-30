#include <iostream>

class myClass
{
	static inline int s_count = 0; 
				/*
				this count variable is now a global variable because of the static keyword
				but is scope to specifically the myClass for our uses, and cannot be used
				outside of this cpp file.
				*/

	int m_myInt;

public:
	myClass(int number) : m_myInt(number)
	{
		++s_count;
	}
	~myClass()
	{
		--s_count;
	}

	int GetInt() const { return m_myInt; }
	int SetInt(int number) { m_myInt = number; }
	/*
		These functions implicitely send the function a pointer of the class it contains
		it actually does this 
		int GetInt(const myClass* this) const { return this->m_myInt; }
		int GetInt(myClass* this , int number) { this->m_myInt = number; }
	*/
	static int GetCount() {return s_count;}
	/*
		This does NOT send the class, so the above line is literally what happens
		so if I want to call this, I do not need an instance of the object
		since it does not require it as part of the function parameters

	*/


};

int main()
{
	std::cout << myClass::GetCount();

}