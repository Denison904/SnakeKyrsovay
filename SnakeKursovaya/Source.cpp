// Version 0.1.0;
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>



using namespace std;
const int width = 40;
const int high = 20;

string map[] = { "########################################",
				"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	"#                                      #",
	 "########################################"
};

			


class Fruit {
public:
	void set() { x = rand() % (width - 2) + 1; y = rand() % (high - 2) + 1; }
	int getX() { return x; }
	int getY() { return y; }
protected:
	int x, y;
};





class Snake {
public:
	int getCourse() { return course; }
	int getX() { return x; }
	int getY() { return y; }
	int getBody(){ return body; }
	void setX(int t) { x += t; }
	void setY(int t) { y += t; }
	void setBody() {  body++; }
	void setCourse(int x) { course = x; };
	int getTailX(int i) { return TailX[i]; }
	int getTailY(int i) { return TailY[i]; }
	void MoveTail();
	void setTail(int x, int y) { TailX.push_back(x); TailY.push_back(y); }
	Snake();
private:
	int body, x , y , course ;	
	vector<int> TailX;
	vector<int> TailY;
};

void Snake::MoveTail() {
	for (int i = getBody()-1;i>0 ; i--)
	{
		TailX[i] = TailX[i - 1];
		TailY[i] = TailY[i - 1];
	}
	TailX[0] = getX();
	TailY[0] = getY();

}


Snake::Snake() {
	body = 1, x = width / 2, y = high / 2, course = 0;
	TailX.push_back(x + 1);
	TailY.push_back(y);
}




class Game :public Snake, public Fruit{
public:
	void Input();
	void Logic();
	void Draw();
	void setAlive() { alive = false; }
	bool getAlive() { return alive; }
	void setSource() { source += 10*getSpeed(); }
	int getSource() { return source; }
	void setSpped(int x) { speed = x; }
	int getSpeed() { return speed; }
	bool Proverka(int j, int i);
private:
	bool alive = true;
	int source = 0, speed=1;
};



bool Game::Proverka(int x, int y) {
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
				else if (Proverka(j,i))
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

}


void Game::Input() {
	char a;
	a = _getche();
	switch (a)
	{
	case 'a': if (Snake::getCourse() != 2) Snake::setCourse(0); break;
	case 'w': if (Snake::getCourse() != 3) Snake::setCourse(1); break;
	case 'd': if (Snake::getCourse() != 0) Snake::setCourse(2); break;
	case 's': if (Snake::getCourse() != 1) Snake::setCourse(3); break;
	}

}

void Game::Logic() {
	if (Snake::getX() == Fruit::getX() && Snake::getY() == Fruit::getY()) {
		int x,y;
		
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
	
	if (Snake::getX() == 0 || Snake::getX() == width - 1 || Snake::getY()== 0 || Snake::getY()== high - 1) {
		setAlive();
		system("cls");
		cout << "GAME OVER 1!\nSOURSE = "<<getSource();
		exit(0);
		
	}
	else if (Proverka( Snake::getX(),Snake::getY()))
		{
			setAlive();
			system("cls");
			cout << "GAME OVER! 2\nSOURCE = " << getSource() << endl;
			exit(0);
		}


	
}


int main() {
	Game game;
	game.Fruit::set();
	game.Draw();

	while (true) {
		game.Input();
		game.Logic();
		game.Draw();
	}

	return 0;
}