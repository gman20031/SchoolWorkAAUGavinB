#include <iostream>

/*
	Known Operators not covered here
	assignment  (  =  ) 
	Arithmetic operators ( + , - , * , / , % )
	Compound assignment ( += , -= , *= , /= , %= , >>= , <<= , &= , ^= , |=)
	Increment and decrement (++, --)
	Relational and comparison operators ( ==, !=, >, <, >=, <= )
	Logical operators ( !, &&, || )
*/

#define print(str) std::cout << str << std::endl;

int main()
{
	char left = 'L';
	char right = 'R';

	// ---------- The ? Operator <Conditional Ternary Operator> -----------
	// --------------------------------------------------------------------
	// Syntax :								Used for quick if statements
	// Condition ? result1 : result2;  
	print("? Operator");

	print((5 > 10 ? left : right));   // first compares left to right
								// if true, returns left
								// otherwise it returns right
								// will print right in this case

	// is simply Boolean statment ? trueResult : falseResult;
	print((true ? left : right));
	print((false ? left : right));

	
	// ---------- The , Operator <Comma operator> -------------------------
	// --------------------------------------------------------------------
	// Syntax :  		Used to seperate two or more expressions where one is expected
	// (expressionOne , expressionTwo , ...) 
	print("comma Operator");

	int a , b;
	int a = (b = 3 , b + 2);
	for( int i = 0, int *p = &i ; i < b ; ++i)
	{

	}

}