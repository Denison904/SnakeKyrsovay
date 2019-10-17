#include "Global.h"
#include "Snake.h"

void Snake::MoveTail() {
	for (int i = getBody()-1;i>0 ; i--)
	{
		TailX[i] = TailX[i - 1];
		TailY[i] = TailY[i - 1];
	}
	TailX[0] = getX();
	TailY[0] = getY();

}

int Snake::mind() {
	int up, down, left, right;
	int sensorF[9][9][4], sensorB[9][9][4];
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (i!=5&&j!=5)
			{
				for (int k = 0; k < 4; k++)
				{
					sensorB[i][j][k] = SensorBorder::get(i, j);
					sensorF[i][j][k] = SensorFood::get(i, j);
				}
			}
		}
	}
	
}

Snake::Snake() {
	body = 3;
	x = width / 2;
	y = high / 2;
	course = 0;
	for (int i = 0; i < body; i++) {
		setTail(x + i + 1, y);
	}
}