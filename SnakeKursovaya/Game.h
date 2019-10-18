#pragma once
#include "Snake.h"
#include "Fruit.h"
#include "Neuron.h"

class Game {
public:
	Game();
	void Input();
	void InputH();
	void InputAI();
	void InputN();
//	void toStudy();
	void Logic();
	void Draw();
	void setAlive() { alive = false; }
	bool getAlive() { return alive; }
	void setSource() { source += 10 * getSpeed(); }
	int getSource() { return source; }
	void setSpped(int x) { speed = x; }
	int getSpeed() { return speed; }
	bool Check(int x, int y);
	int GetFruitX() { return fruit.getX(); }
	int GetFruitY() { return fruit.getY(); }
	void setIteration() { iteration++; }
private:
	Fruit fruit;
	Snake snake;
	//NetWork nn;
	bool alive = true;
	int source = 0, speed = 1;
	int iteration = 0;
	char A, Study;

	/*
	const int input_l = 160;
	const int l = 4;
	

	double input[160];
	double result;
	int rresult;
	double ra = 0;
	int maxra = 0;
	int maxraepoch = 0;
	int size[4] = { input_l, 64,32,4 };
	int n = 10;
	double time = 0;
	Data* data = new Data[n];*/
};