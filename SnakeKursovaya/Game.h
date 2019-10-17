#pragma once
#include "Snake.h"
#include "Fruit.h"


class Game :public Snake, public Fruit {
public:
	void Input();
	void Logic();
	void Draw();
	void setAlive() { alive = false; }
	bool getAlive() { return alive; }
	void setSource() { source += 10 * getSpeed(); }
	int getSource() { return source; }
	void setSpped(int x) { speed = x; }
	int getSpeed() { return speed; }
	bool Check(int x, int y);
	void setIteration() { iteration++; }
private:
	bool alive = true;
	int source = 0, speed = 1;
	int iteration = 0;
};