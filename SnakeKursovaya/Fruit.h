#pragma once


class Fruit {
public:
	void set();
	int getX() { return x; }
	int getY() { return y; }
protected:
	int x, y;
};