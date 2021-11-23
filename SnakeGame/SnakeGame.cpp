// SnakeGame.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Raikov Maxim BSBO-13-20
#include<windows.h>
#include <iostream>
#include <conio.h>
using namespace std;
bool gameOver;
const int width = 30;
const int heigth = 30; 

int x, y, fruitX, fruitY, score; 
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection eDir; 
//Arrays for coordinates of segments 
int tailX[100], tailY[100];
//Length if tail; 
int nTail = 0;


void Setup() {

	gameOver = false; 
	x = width / 2;
	y = heigth / 2;
	//fruit coordinates in field
	fruitX = rand() % (width-2); 
	fruitY = rand() % (heigth-2); 
	score = 0;



}

void ClearScreen()
{
	COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void Drawing() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//Drawing map
	ClearScreen();

	for (int i = 0; i <= width; i++) {
		cout << "#";
	}
	 cout << endl; 

	for (int i = 0; i < heigth; i++) {
		for (int j = 0; j <= width; j++) {
			SetConsoleTextAttribute(hConsole, 7);
			if (j == 0 || j == width - 1) {
				cout << "#";
				if (j == width - 1) {
					SetConsoleTextAttribute(hConsole, 13);
					switch (i) {
					case 0:
						cout << "                              CONTROLS:";
						break;
					case 1:
						cout << "                              W - UP";
						break;
					case 2:
						cout << "                              A - LEFT";
						break;
					case 3:
						cout << "                              S - DOWN";
						break;
					case 4:
						cout << "                              D - RIGHT";
						break;
					case 5:
						cout << "                              0 - EXIT";
						break;
					case 6:
						cout << "                              r - RESTART";
						break;
					}



					
				}
			}

			if (i == y && j == x) {
				SetConsoleTextAttribute(hConsole, 10);
				cout << "O";
			}
		
			else if (i == fruitY && j == fruitX) {
				SetConsoleTextAttribute(hConsole, 2);
				cout << "*";
			}

			else {
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{

					if (tailX[k] == j && tailY[k] == i)
					{
						SetConsoleTextAttribute(hConsole, 10);
						cout << "o";
						print = true; 
					}

				}
				if (!print)
					cout << " ";
			}

	
		}
		cout << endl; 
	}


	for (int i = 0; i <= width; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score<<endl; 

	Sleep(20);
}
void CheckInput() {
	//if keyboard pressed
	if (_kbhit()) {
		//get key
		switch (_getwch()) {
		case  'w':
			eDir = UP;
			break;
		case  'a':
			eDir = LEFT;
			break;
		case  's':
			eDir = DOWN;
			break;
		case  'd':
			eDir = RIGHT;
			break;
		case '0': //Leave game
			gameOver = true; 
			exit(0);
			break;
		}
	}
}
void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];

	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (eDir) {
	case UP:
		Sleep(50);
		y--;
		break;
	case LEFT:
		Sleep(10);
		x--;
		break;
	case DOWN:
		Sleep(50);
		y++;
		break;
	case RIGHT:
		Sleep(10);
		x++;
		break;
	defaut:
		break;
	}
	/* 

	if (x >= width -1 || x < 0 || y >= heigth || y < 0)
		gameOver = true; 
			*/
	
	if (x >= width-1)
		x = 0;
	if (x < 0)
		x = width-2;
	if (y >= heigth)
		y = 0;
	if (y < 0)
		y = heigth;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}

	}
	if (x == fruitX && y == fruitY) {
		nTail++;
		score += 10;
		fruitX = rand() % (width-2);
		fruitY = rand() % (heigth-2);
	}

}


int main()
{
	Setup();
	while (true) {
		while (!gameOver) {
			Drawing();
			Logic();
			CheckInput();
		}
		
		cout << "You have lost, press r to restart or any other key to exit" << endl;
		while (gameOver) {
			if (_getch() == 'r') {
				nTail = 0;
				system("cls");
				Setup();
			}
			else{
				exit(0);
			}

		}
	}
	

	
}

