#pragma once
#include "Snake.h"
#include "Fruit.h"


class Game {
public:
	Game();
	void Input();
	void InputH();
	void InputAI();
	void InputN();
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
	char A;
	bool alive = true;
	int source = 0, speed = 1;
	int iteration = 0;
};