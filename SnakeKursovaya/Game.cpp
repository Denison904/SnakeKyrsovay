#include "Global.h"
#include "Game.h"
#include <ctime>

bool Game::Check(int x, int y) {
	for (int i = 0; i < Snake::getBody(); i++)
	{
		if (Snake::getTailX(i) == x && Snake::getTailY(i) == y) return true;
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
				else if (i == Snake::getY() && j == Snake::getX())
				{
					cout << "@";
				}
				else if (Check(j, i))
				{
					cout << "o";
				}
				else  if (i == Fruit::getY() && j == Fruit::getX()) {
					cout << "F";
				}
				else cout << " ";
			}
			cout << '\n';
		}
	}
	cout << endl << Snake::getCourse();
	setIteration();

}


void Game::Input() {
	/*char a;
	a = _getche();
	switch (a)
	{
	case 'a': if (Snake::getCourse() != 2) Snake::setCourse(0); break;
	case 'w': if (Snake::getCourse() != 3) Snake::setCourse(1); break;
	case 'd': if (Snake::getCourse() != 0) Snake::setCourse(2); break;
	case 's': if (Snake::getCourse() != 1) Snake::setCourse(3); break;
	}*/
	int a;
	srand(static_cast<unsigned int>(time(0)));
	a = rand() % 3;
	switch (a)
	{
	case 0: if (Snake::getCourse() != 2) Snake::setCourse(0); break;
	case 1: if (Snake::getCourse() != 3) Snake::setCourse(1); break;
	case 2: if (Snake::getCourse() != 0) Snake::setCourse(2); break;
	case 3: if (Snake::getCourse() != 1) Snake::setCourse(3); break;
	}
}


void Game::Logic() {
	if (Snake::getX() == Fruit::getX() && Snake::getY() == Fruit::getY()) {
		int x, y;

		x = Snake::getTailX(Snake::getBody() - 1);
		y = Snake::getTailY(Snake::getBody() - 1);
		Snake::MoveTail();
		Snake::setTail(x, y);
		Snake::setBody();
		setSource();
		Fruit::set();
	}
	else MoveTail();
	switch (Snake::getCourse())
	{
	case 0: Snake::setX(-1); break;
	case 1: Snake::setY(-1); break;
	case 2: Snake::setX(1); break;
	case 3: Snake::setY(1); break;
	}

	if (Snake::getX() == 0 || Snake::getX() == width - 1 || Snake::getY() == 0 || Snake::getY() == high - 1) {
		setAlive();
		system("cls");
		cout << "GAME OVER 1!\nSOURSE = " << getSource() << "\nIteration = " << iteration << endl;
		exit(0);

	}
	else if (Check(Snake::getX(), Snake::getY()))
	{
		setAlive();
		system("cls");
		cout << "GAME OVER! 2\nSOURCE = " << getSource() << "\nIteration = " << iteration << endl;
		exit(0);
	}



}