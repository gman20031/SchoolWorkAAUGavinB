#include <iostream>

int main()
{
    std::string name = "Carl";
    int score = 10'000; // single quote can be used, optionally
    bool didWin = true; 
    char firstInitial = 'S';
    
    // once declared, a variable can generally 
    // ONLY be assigned a value of the correct type
    //name = false;     // std::string = bool  // not allowed

    // variables are uninitialized until they are assigned.
    // an uninitialized variable should never be read.
    int playerScore = 20000;
    std::cout << playerScore;

    playerScore += 1000;    // playerScore = playerScore + 1000;
    //playerScore = +1000;    // NOT the same!
    //playerScore = -1000;    //

    // these will round off differently
    float pi = 3.14159265359f;          // Accurate to about ~6 digits after the decimal
    double doublePi = 3.14159265359;   // Accurate to all digits, but adds 1e-10 or so

    int x = 5;
    int y = ++x;    // y -> 6; additions happens before!

    x = 5;
    y = x++;    // y -> 5; addition happens after!

    // (ADVANCED) Don't write code like this... will it be true?
    if ((x++) + x == 10 && (x++) + x == 12)
        std::cout << "yikes\n";


    return 0;
}