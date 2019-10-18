#include "Global.h"
#include "SensorFood.h"

using namespace std;


void SensorFood::set() {
	int x, y, k = 0, xf, yf;
	ifstream fin;
	fin.open("Fruit.txt");
	ofstream fout;
	fout.open("Bridge.txt");
	x = this->getX() - 4;
	y = this->getY() - 4;
	for (int i = 0; i < this->getBody(); i++)
	{
		for (int j = 0; j < this->getBody(); j++)
		{
			if (i != 5 && j != 5)
			{
				fin >> xf;
				fin >> yf;
				//for()
				if (x + i == xf && y + j == yf)
				{
					input[k] = 1;
				}
				else
				{
					input[k] = 0;
				}
				fout << input[k++] << " ";
			}

		}
	}
}