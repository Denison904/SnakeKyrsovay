#include "Global.h"
#include "Game.h"
#include "Sensor.h"
#include <ctime>
#include <random>
#include <conio.h>
#include <fstream>
#include <vector>




void Game::Input(int a) {
	switch (a)
	{
	case '0':
		if (snake.getCourse() != 2) snake.setCourse(0);
		break;
	case '1':
		if (snake.getCourse() != 3) snake.setCourse(1);
		break;
	case '2':
		if (snake.getCourse() != 0) snake.setCourse(2);
		break;
	case '3':
		if (snake.getCourse() != 1) snake.setCourse(3);
		break;
	}
}


void toStudy() {
	//int rresult[4];
	int index;
	char rr;
	search();
	net.Input(snake.sensor.input);
	net.ForwardFeed();
	net.max();
	int k = 0;
	cout << "\nSensor border:\n";
	for (int i = 0; i < sqrt(net.size[0]/2); i++)
	{
		for (int j = 0; j < sqrt(net.size[0]/2); j++)
		{
			cout << net.input[k++].value << " ";
		}
		cout<<endl;
	}
	cout << "\nSensor fruit:\n";
	for (int i = 0; i < sqrt(net.size[0] / 2); i++)
	{
		for (int j = 0; j < sqrt(net.size[0] / 2); j++)
		{
			cout << net.input[k++].value << " ";
		}
		cout << endl;
	}
	switch (net.max())
	{
	case 0:
		cout << "Prediction is left :" << net.max() << endl;;
		for (int  i = 0; i < 4; i++)
		{
			cout<<  net.output[i].value << endl;
		}
		
		break;
	case 1:
		cout << "Prediction is up :" << net.max() << endl;;
		for (int i = 0; i < 4; i++)
		{
			cout << net.output[i].value << endl;
		}

		break;
	case 2:
		cout << "Prediction is right :" << net.max() << endl;;
		for (int i = 0; i < 4; i++)
		{
			cout << net.output[i].value << endl;
		}

		break;
	case 3:
		cout << "Prediction is down :" << net.max() << endl;;
		for (int i = 0; i < 4; i++)
		{
			cout << net.output[i].value << endl;
		}

		break;
	default:
		break;
	}
	double rresult[4];;
	rr = _getch();
	switch (rr)
	{
	case 'A': case'a':
		for (int i = 0; i < 4; i++)
		{
			if (i == 0) {
				rresult[i] = 1;
			}
			else
			{
				rresult[i] = 0;
			}

		}
		index = 0;
		break;
	case 'w': case 'W':
		for (int i = 0; i < 4; i++)
		{
			if (i == 1) {
				rresult[i] = 1;
			}
			else
			{
				rresult[i] = 0;
			}

		}
		index = 1;
		break;
	case 'd':case 'D':
		for (int i = 0; i < 4; i++)
		{
			if (i == 2) {
				rresult[i] = 1;
			}
			else
			{
				rresult[i] = 0;
			}

		}
		index = 2;
		break;
	case 's' : case 'S':
		for (int i = 0; i < 4; i++)
		{
			if (i == 3) {
				rresult[i] = 1;
			}
			else
			{
				rresult[i] = 0;
			}

		}
		index = 3;
		break;
	default:
		break;
	}

	for (int i = 0; i < 4; i++)
	{
		
	}

	//double test[4];
	for (int i = 0; i < 4; i++)
	{
		net.RightResult[i].push_back(rresult[i]);
		net.tmpoutput[i].push_back(net.output[i].value);
	}
	
	for (int i = 0; i < net.size[0]; i++)
	{
		net.tmpinput[i].push_back(snake.sensor.input[i]);
	}

	snake.setCourse(index);
}
void Game::search() {
	int x0 = snake.getX() - 5, y0 = snake.getY() - 5, k = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((i != 5) || (j != 5))
			{	
				if (Border(x0 + j, y0 + i))
					snake.sensor.input[k++] = 1;
				else snake.sensor.input[k++] = 0;
			}
			else
			{
				snake.sensor.input[k++] = 1;
			}
		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if ((i != 5) || (j != 5))
			{
				if (checkFruit(x0 + j, y0 + i))
					snake.sensor.input[k++] = 1;
				else snake.sensor.input[k++] = 0;
			}
			else
			{
				snake.sensor.input[k++] = snake.getCourse();
			}
		}
	}
}

bool Game::checkTail(int x0, int y0) {
	for (int i = 0; i < snake.getBody(); i++)
	{
		if (x0 == snake.getTailX(i) && y0 == snake.getTailY(i))
			return true;
	}
	return false;
}

bool Game::Border(int x0, int y0) {
	if (x0 <= 0 || y0 <= 0 || x0 >= width - 1 || y0 >= high - 1)
		return true;
	else if (Check(x0, y0)) //(checkTail(x0, y0))
		return true;
	else return false;
}

bool Game::checkFruit(int x0, int y0) {
	for (int i = 0; i < 10; i++)
	{
		if (fruit[i].getX() == x0 && fruit[i].getY() == y0)
		return true;
	}
	
	return false;
}

bool Game::Check(int x, int y) {
	for (int i = 0; i < snake.getBody(); i++)
	{
		if (snake.getTailX(i) == x && snake.getTailY(i) == y) return true;
	}
	return false;

}

void Game::Alive() {
	alive = true;
	Snake snake;
}



void Game::Draw() {

	if (getAlive())
	{
		system("cls");
	//	cout << "Epoch = " << << endl;
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
				else  if (checkFruit(j,i)) {
					cout << "F";
				} 
				else cout << " ";
			}
			cout << '\n';
		}
	}
	cout << endl << snake.getCourse() << endl;
	//setIteration();
}





void Game::Logic() {
	switch (snake.getCourse())
	{
	case 0: snake.setX(-1); break;
	case 1: snake.setY(-1); break;
	case 2: snake.setX(1); break;
	case 3: snake.setY(1); break;
	}
	int tmp = 0;
	for (int i = 0; i < 10; i++)
	{
	if (snake.getX() == fruit[i].getX() && snake.getY() == fruit[i].getY()) {
		int x, y;
		x = snake.getTailX(snake.getBody() - 1);
		y = snake.getTailY(snake.getBody() - 1);
		snake.MoveTail();
		snake.setTail(x, y);
		snake.setBody();
		setSource();
		fruit[i].set();
		while (Check(fruit[i].getX(), fruit[i].getY()) || (fruit[i].getX()==snake.getX() && fruit[i].getY() == snake.getY()) )
		{
			fruit[i].set();
		}
		tmp = 1;
	}
	
	}
	if(!tmp) snake.MoveTail();


	if (snake.getX() == 0 || snake.getX() == width - 1 || snake.getY() == 0 || snake.getY() == high - 1) {
		setAlive();
		system("cls");
		cout << "GAME OVER 1!\nSOURSE = " << getSource() << "\nIteration = " << iteration << endl;
		

	}
	else if (Check(snake.getX(), snake.getY()))
	{
		setAlive();
		system("cls");
		cout << "GAME OVER! 2\nSOURCE = " << getSource() << "\nIteration = " << iteration << endl;
		
	}
	
	

}



void Game::Weights(){
	fstream f;
	cout << "ENTER FILENAME \n";
	string filename;
	cin >> filename;
	f.open(filename);
}