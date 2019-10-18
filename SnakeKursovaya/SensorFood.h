#pragma once
#include "Snake.h"

class SensorFood:public Snake {
public:
	void set();
	int get(int i) { return input[i]; }
private:
	int input[80];
};