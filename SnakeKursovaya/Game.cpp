#include "Global.h"
#include "Game.h"
#include "SensorBorder.h"
#include "SensorFood.h"
#include <ctime>
#include <random>
#include <conio.h>
Game::Game() {
	
	cout << "Enter h(human) or a(artificial intelligence) or n(Neural Network): ";
	cin >> A;
	if (A=='n'||A=='N')
	{
		cout << "Do you want to study Snake? (y/n) \n";
		cin >> Study;
	}
	fruit.set();
	fruit.set();
}

void Game::Input() {

	switch (A)
	{
	case 'H': this->InputH(); break;
	case 'h': this->InputH(); break;
	case 'A' :this->InputAI(); break;
	case'a':this->InputAI(); break;
	case 'N':this->InputN(); break;
	case 'n' :this->InputN(); break;
	default:
		cout << "\nError you enter false kay!\n";
		setAlive();
		exit(1);
		break;
	}
}
/*
void Game::toStudy() {

	ifstream fin;
	ofstream fout;
	fin.open("Bridge.txt");
	fout.open("log.txt");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < input_l; j++) {
			fin >> data[i].info[j];
		}
		fin >> data[i].rresult;
		data[i].rresult -= 65;
	}

	nn.setLayers(l, size);
	for (int e = 0; ra / n * 100 < 100; e++) {
		//cout << "Epoch #" << e << endl;
		fout << "Epoch # " << e << endl;
		double epoch_start = clock();
		ra = 0;
		double w_delta = 0;



		for (int i = 0; i < n; i++) {

			for (int j = 0; j < 160; j++) {
				input[j] = data[i].info[j];
			}
			rresult =data[i].rresult;
			//cout << int(rresult) << endl;
			//cout << "Цифра " << rresult << endl;
			nn.setInput(input);
			double FF_start = clock();

			this->result = nn.ForwardFeed();

			double FF_stop = clock();
			//cout << "ForwardFeed Time: " << FF_stop - FF_start << endl;
			//nn.show();
			if (result == rresult) {
				//cout << "Результат верный!\n";
				cout << "Угадал ход " << "\t\t\t****\n" << endl;
				ra++;
			}
			else {
				//cout << "Результат " << result << " неверный!\n";
				//cout << "Не угадал букву " << char(rresult + 65) << "\n";
				double BP_start = clock();
				nn.BackPropogation(result, rresult, 0.5);
				double BP_stop = clock();
				//cout << "BackPropogation time: " << BP_stop - BP_start << endl;
			}
		}

		double epoch_stop = clock();
		cout << "Right answers: " << ra / n * 100 << "% \t Max RA: " << double(maxra) / n * 100 << "(epoch " << maxraepoch << " )" << endl;
		time = 0;
		//cout << "W_Delta: " << w_delta << endl;
		if (ra > maxra) {
			maxra = ra;
			maxraepoch = e;
		}
		if (maxraepoch < e - 250) {
			maxra = 0;
		}
	}
}
*/


void Game::InputN() {
	if (Study == 'y' || Study == 'Y') this->toStudy();
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

