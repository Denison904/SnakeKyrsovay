#include "Global.h"
#include "Game.h"
#include <ctime>
#include <random>
#include <conio.h>
Game::Game() {
	fruit.set();
	cin >> A;
}

void Game::Input() {

	switch (A)
	{
	case 'H' || 'h': this->InputH(); break;
	case 'A':this->InputAI(); break;
	case'a':this->InputAI(); break;
	case 'N' :this->InputN(); break;
	default:
		cout << "\nError you enter false kay!\n";
		setAlive();
		exit(1);
		break;
	}
}

void Game::InputN() {
}

bool Game::Check(int x, int y) {
	for (int i = 0; i < snake.getBody(); i++)
	{
		if (snake.getTailX(i) == x && snake.getTailY(i) == y) return true;
	}
	return false;

}


void Game::Draw() {

	if (getAlive())
	{
		system("cls");
		for (int i = 0; i < high; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || j == 0 || i == high - 1 || j == width - 1)
				{
					cout << "#";
				}
				else if (i == snake.getY() && j == snake.getX())
				{
					cout << "@";
				}
				else if (Check(j, i))
				{
					cout << "o";
				}
				else  if (i == fruit.getY() && j == fruit.getX()) {
					cout << "F";
				}
				else cout << " ";
			}
			cout << '\n';
		}
	}
	cout << endl << snake.getCourse();
	setIteration();

}
void Game::InputH() {
	char a;
	a = _getche();
	switch (a)
	{
	case 'a': if (snake.getCourse() != 2) snake.setCourse(0); break;
	case 'w': if (snake.getCourse() != 3) snake.setCourse(1); break;
	case 'd': if (snake.getCourse() != 0) snake.setCourse(2); break;
	case 's': if (snake.getCourse() != 1) snake.setCourse(3); break;
	}
}

void Game::InputAI() {

	int a;
	random_device rd;
	mt19937 mersenne(rd());
	a = mersenne() % 3;
	switch (a)
	{
	case 0: if (snake.getCourse() != 2) snake.setCourse(0); break;
	case 1: if (snake.getCourse() != 3) snake.setCourse(1); break;
	case 2: if (snake.getCourse() != 0) snake.setCourse(2); break;
	case 3: if (snake.getCourse() != 1) snake.setCourse(3); break;
	}
}


void Game::Logic() {
	if (snake.getX() == fruit.getX() && snake.getY() == fruit.getY()) {
		int x, y;

		x = snake.getTailX(snake.getBody() - 1);
		y = snake.getTailY(snake.getBody() - 1);
		snake.MoveTail();
		snake.setTail(x, y);
		snake.setBody();
		setSource();
		fruit.set();
	}
	else snake.MoveTail();
	switch (snake.getCourse())
	{
	case 0: snake.setX(-1); break;
	case 1: snake.setY(-1); break;
	case 2: snake.setX(1); break;
	case 3: snake.setY(1); break;
	}

	if (snake.getX() == 0 || snake.getX() == width - 1 || snake.getY() == 0 || snake.getY() == high - 1) {
		setAlive();
		system("cls");
		cout << "GAME OVER 1!\nSOURSE = " << getSource() << "\nIteration = " << iteration << endl;
		exit(0);

	}
	else if (Check(snake.getX(), snake.getY()))
	{
		setAlive();
		system("cls");
		cout << "GAME OVER! 2\nSOURCE = " << getSource() << "\nIteration = " << iteration << endl;
		exit(0);
	}



}

