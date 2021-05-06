#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

bool gameOver;
const int width		= 20;
const int heigth	= 20;

const int sScreenWidth	= width;
const int sScreenHeigth = 3;

double speed = 0;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

int getRandrom(int min, int max) {
	return (((double(max) - double(min) + 1.0) * double(rand())) / (static_cast<double>(RAND_MAX) + 1.0)) + min;
}

void spawnFruit() {
	fruitX = getRandrom(1, width - 2);
	fruitY = getRandrom(1, heigth - 2);
	for (int k = 0; k < nTail; ++k) {
		if (tailX[k] == fruitX && tailY[k] == fruitY) {
			spawnFruit();
			break;
		}
	}
}

void Setup() {
	srand(time(0));
	gameOver = false;
	dir = eDirection::STOP;
	speed = 1;
	score = 0;
	nTail = 0;
	x = width	/ 2 - 1;
	y = heigth	/ 2 - 1;
	spawnFruit();
}

void drowSScreen(string info1 = "", string info2 = "", string info3 = "") {
	for (int i = 0; i < sScreenWidth; ++i) {
		cout << "-";
	}
	cout << endl;
	for (int h = 0; h < sScreenHeigth; ++h) {
		for (int i = 0; i < sScreenWidth; i++) {
			if (i == 0 || i == sScreenWidth - 1)
				cout << "|";
			else
				if (info1 != "" && h == 0 && i == (sScreenWidth / 2 - (info1.length()) / 2)) {
					cout << info1;
					i += (info1.length() - 1);
				}
				else if (info2 != "" && h == 1 && i == ((sScreenWidth / 2) - (info2.length()) / 2)) {
					cout << info2;
					i += (info2.length() - 1);
				}
				else if (info3 != "" && h == 2 && i == ((sScreenWidth / 2) - (info3.length()) / 2)) {
					cout << info3;
					i += (info3.length() - 1);
				}
				else {
					cout << " ";
				}
		}
		cout << endl;
	}
	for (int i = 0; i < sScreenWidth; ++i) {
		cout << "-";
	}
	cout << endl;
}

void Draw() {
	system("cls");
	drowSScreen("by 30zero", "", "score: " + std::to_string(score));
	cout << endl;
	for (int i = 0; i < width; ++i) {
		cout << "#";
	}
	cout << endl;

	for (int i = 1; i < heigth - 1; ++i) {
		for (int j = 0; j < width; ++j) {
			if (j == 0 || j == width - 1)
				cout << "#";
			else if (i == y && j == x)
				cout << "0";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool tail = false;
				for (int k = 0; k < nTail; ++k) {
					if (tailX[k] == j && tailY[k] == i) {
						tail = true;
						break;
					}
				}
				if (tail) cout << "o";
				else cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width; ++i) {
		cout << "#";
	}
	cout << endl;
}

void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			if (dir != eDirection::RIGHT)
				dir = eDirection::LEFT;
			break;
		case 'd':
			if (dir != eDirection::LEFT)
				dir = eDirection::RIGHT;
			break;
		case 'w':
			if (dir != eDirection::DOWN)
				dir = eDirection::UP;
			break;
		case 's':
			if (dir != eDirection::UP)
				dir = eDirection::DOWN;
			break;
		default:
			break;
		}
	}
}

void Logic() {
	int prevX = x;
	int prevY = y;
	for (int i = 0; i < nTail; ++i) {
		std::swap(prevX, tailX[i]);
		std::swap(prevY, tailY[i]);
	}


	switch (dir)
	{
	case eDirection::LEFT:
		x--;
		break;
	case eDirection::RIGHT:
		x++;
		break;
	case eDirection::UP:
		y--;
		break;
	case eDirection::DOWN:
		y++;
		break;
	default:
		break;
	}

	switch (x)
	{
	case width-1:
		x = 1;
		break;
	case 0:
		x = width - 2;
		break;
	default:
		break;
	}
	
	switch (y)
	{
	case heigth - 1:
		y = 1;
		break;
	case 0: 
		y = heigth - 2;
		break;
	default:
		break;
	}

	for (int k = 0; k < nTail; ++k) {
		if (tailX[k] == x && tailY[k] == y) {
			gameOver = true;
			cout << "GAME OVER" << endl;
			break;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		speed += 0.2;

		spawnFruit();
		nTail++;
	}
}




int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Sleep((1/speed) * 500);
		Logic();
	}



	return 0;
}