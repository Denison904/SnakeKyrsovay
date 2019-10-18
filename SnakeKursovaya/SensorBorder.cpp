#include "Global.h"
#include "SensorBorder.h"
using namespace std;

bool SensorBorder::check(int x, int y) {
	if (x <= 0 || y <= 0 || y >= high - 1 || x >= width - 1) return true;
	else {
		for (int i = 0; i < this->getBody(); i++)
		{
			if (x == this->getTailX(i) && y == this->getTailY(i)) return true;
		}
	}
	return false;
}

void SensorBorder::set() {
	int x, y, k = 0;
	x = this->getX()-4;
	y = this->getY()-4;
	for (int  i = 0; i < this->getBody(); i++)
	{
		for (int j = 0; j < this->getBody(); j++)
		{
			if (i!=5&&j!=5)
			{
				if (check(x+i, y+j)) input[k] = 1;
				else input[k] = 0;
				k++;
			}
			
		}
	}
}
