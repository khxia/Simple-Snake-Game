#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameover;
int x, y, FruitX, FruitY, Score;
const int width = 30;
const int height = 16;
enum Direction_snake {STOP = 0, LEFT, RIGHT, UP, DOWN};
Direction_snake dir;
int tailX[100], tailY[100];
int nTail;

void Setup() 
{
	gameover = false;
	x = width / 2;
	y = height / 2;
	FruitX = rand() % width;
	FruitY = rand() % height;
	Score = 0;
	dir = STOP;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			else if (i == y && j == x)
				cout << "O";
			else if (i == FruitY && j == FruitX)
				cout << "X";
			else if (j == (width - 1))
				cout << "#";
			else
			{
				bool printed = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						printed = true;
					}
				}
				if (printed == false)
				{
					cout << " ";
				}
			}

		}
		cout << endl;
	}
	
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << Score << endl; 



}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		default:
			dir = STOP; 
			break;
			
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) // Don't understand this for loop
	{
		prev2X = tailX[i]; 
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
		if (x == tailX[i] && y == tailY[i])
			gameover = true;

	}
	
	/*for (int i = nTail - 1; i > 0; i--)
	{
		tailX[i] = tailX[i - 1];
		tailY[i] = tailY[i - 1];
	}
*/
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP: 
		y--;
		break;
	case DOWN:
		y++;
		break;
	case STOP:
		break;
	

	}
	if (x > width) x = 0; else if (x < 0) x = width - 1;
	if (y > height) y = 0; else if (y < 0) y = height - 1;
	
	if (x == FruitX && y == FruitY) 
	{
		Score += 10;
		FruitX = rand() % width;
		FruitY = rand() % height;
		nTail++;

	}
	
}

int main() 
{
	std::cout << "First Game in C++\n" ;
	Setup();
	while (!gameover)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}
	std::cout << "GAME OVER";
	return 0;
}