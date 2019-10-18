#include "Global.h"
#include "SensorFood.h"

using namespace std;


void SensorFood::set() {
	int x, y, k = 0;
	x = this->getX() - 4;
	y = this->getY() - 4;
	for (int i = 0; i < this->getBody(); i++)
	{
		for (int j = 0; j < this->getBody(); j++)
		{
			if (i != 5 && j != 5)
			{
			//	if (x+i==Fruit::getX() &&y+i==Fruit::getY()) input[k] = 1;
			//	else input[k] = 0;
			//	k++;
			}

		}
	}
}