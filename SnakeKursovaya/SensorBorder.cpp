#include "Global.h"
#include "SensorBorder.h"
#include <ctime>
using namespace std;

void SensorBorder::set() {
	fstream w;

	w.open("WB.txt");
	w.seekg(0, w.end);
	size_t fileSize = w.tellg();
	if (fileSize == 0) {
		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (i != 5 && j != 5)
				{
					sensor[i][j] = rand() % 200 - 100;
					w << sensor[i][j] << " ";
				}
			}
		}
	}
	else {
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (i != 5 && j != 5)

				{
					w >> sensor[i][j];
				}
			}
		}
	}
}
