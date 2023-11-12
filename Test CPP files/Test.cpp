
#include <iostream>
#include <windows.h>
#include <fstream>

void MoveRight(int *xPos, int *yPos,char *map, int *width);

int GetXAtIndex(int index, int width)
{
	int output = index % width;
	return output;
}

int GetYAtIndex(int index, int width)
{
	int y = index / width;
    return y;
}

int GetIndexAtCoordinates(int x, int y , int width)
{
	int index = x + y * width;
	return index;
}

int main()
{
	int width = 14;
	char map[] {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
				'#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#', 'X', '#',
				'#', '.', '.', '#', '.', '.', '.', '#', '#', '#', '.', '#', '.', '#',
				'#', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '#',
				'#', '.', '#', '#', 'O', '#', '#', '#', '.', '.', '.', '#', '.', '#',
				'#', '.', '.', '.', '.', '.', '.', '.', 'O', '.', '.', '#', '.', '#',
				'#', '.', '#', '#', '#', '#', '.', '#', '!', '.', '.', '#', '.', '#',
				'#', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '#', '.', '#',
				'#', '.', '!', '.', '.', '#', '.', '#', '.', '.', '!', '#', '.', '#',
				'@', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '!', '#',
				'#', '.', '.', '.', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#',
				'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',};

	int xPos = 0;
	int yPos = 3;

	while(true)
	{
		if(GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
		if(GetAsyncKeyState(VK_RIGHT))
		{
			MoveRight(&xPos, &yPos, map, &width);
		}
		for(int i = 0 ; i < (sizeof(map) / sizeof(map[0])); ++i )
		{
			std::cout << map[i] << ' ';
			if( ((i+1) % width) == 0 )
				std::cout << std::endl;
		}

		sleep(33);
		system("cls");
	}

	return 0;
}

void MoveRight(int *xPos, int *yPos,char *map , int *width)
{
	map[GetIndexAtCoordinates(*xPos, *yPos, *width)] = '.';
	++*xPos;
	map[GetIndexAtCoordinates(*xPos, *yPos, *width)] = '@';
}