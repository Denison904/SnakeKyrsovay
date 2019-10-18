#pragma once
#include "Snake.h"

class SensorBorder:public Snake {
public:
	void set();
	bool check(int x, int y);
	int get(int i) { return input[i]; }
private:
	int input[80];
};
