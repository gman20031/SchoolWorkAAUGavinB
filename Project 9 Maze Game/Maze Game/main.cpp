/* Summary of Game

Summary:
The user moves through a maze of walls to find an exit.

Game Specification:
    The user sees the maze in the form of a grid of tiles, with a size of at least 8 x 8.
    Use the '.' character to represent an empty tile.
    Use the '@' character to represent the player character's current position.
    Use the '#' character to represent a wall. The player cannot move through a wall.
    Use the 'X' character to represent the exit. When the player touches this, the game ends in a win.
	use the '!' character to represent enemy. Get sent to the beginning if the player touches the enemy.
	use the 'O' character to represent a trap. Get sent to the beginning if the player touches the trap.
    Do not allow the player character to move off the edges of the map.

	Moving enemies
	Traps
	Multiple Levels (6?)

	1 )				
		# # # # # #			
		# . . . . #
		@ . . . . x
		# . . . . #
		# # # # # #

	2 ) 
		# # # # # # # #
		# . . . . # x #
		# . # # . # . #
		# . . # . . . #
		# # . # # # # #
		@ . . . . . # #
		# # # # . # # #
		# # # . . . . #
		# # # # # # # #

	3 ) 
		# # # # # #			
		# . . ! . #
		@ . . . . x
		# . . . . #
		# # # # # #

	4 ) 
	    # # # # # # # # # # # # #
		# # # # # . . . . . . # #
		# . . # . . # # # # . . #  
		# # . . . # . . . . # . # 
		# # # . # . . # # . # . #
		# . . . . . . . # x # . #
		@ . # # # # ! # # # # # #
		# . # . # # . . . . . # #
		# . # . . . . # # # . # #
		# . . . # # . . . . . # #
		# # # # # # # # # # # # #
							   
	5 ) 
		# # # # # #
		# . O . . #
		@ . O . . x
		# . . . O #
		# # # # # #

	6 )
		# # # # # # # # # # # # # #
		# . . . . # . . . . . # X #
		# . . # . . . # # # . # . #
		# . . # . . . # . . . # . #
		# . # # O # # # . . . # . #
		# . . . . . . . O . . # . #
		# . # # # # . # ! . . # . #
		# . . . . # . # . . . # . #
		# . ! . . # . # . . ! # . #
		@ . . . . # . # . . . . ! #
		# . . . . # . # # # # # . #
		# # # # # # # # # # # # # #
*/

#include <iostream>
#include <string>
#include <vector>

struct enemy 
{
private:
	int xPos = 0;
	int yPos = 0;
	char currentDirection = 'n';
	enum loopType
	{
		clockwiseCircle,
		antiClockCircle,
		horizontal,
		verticle
	};
};

int main()
{

	return 0;
}