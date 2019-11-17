#pragma once
#include "Snake.h"
#include "Fruit.h"
//#include "Neuron.h"
#include "Global.h"
//#include "GANeuron.h"
#include <iostream>
using namespace std;

class Game {
public:
	Game() {};
	void Alive();
	void Input(int a);
	void Logic();
	void Draw();
	void setAlive() { alive = false; }
	bool getAlive() { return alive; }
	void setSource() { source += 10 ; }
	int getSource() { return source; }
	bool Check(int x, int y);
	int GetFruitX(int i) { return fruit[i].getX(); }
	int GetFruitY(int i) { return fruit[i].getY(); }
	void setIteration() { iteration++; }
	void search();//NW
	bool Border(int x0, int y0);//nw
	bool checkTail(int x0, int y0);//
	bool checkFruit(int x0, int y0);//nw;
	~Game() {};
	void Print(int x) { system("cls"); cout << "Epoch = " << x << endl; };
private:
	Fruit fruit[10];
	Snake snake;
	bool alive = true;
	int source = 0, speed = 1;
	int iteration = 0;
	char A, Study;
};