#include "Global.h"
#include "Snake.h"


void Snake::MoveTail() {
	
	for (int i = getBody()-1;i>0 ; i--)
	{
		TailX[i] = TailX[i - 1];
		TailY[i] = TailY[i - 1];
	}
	switch (course)
	{
	case 0:
		TailX[0] = x + 1;
		TailY[0]=y;
		break;
	case 1: 
		TailX[0] = x;
		TailY[0] = y+1;
		break;
	case 2: 
		TailX[0] = x-1;
		TailY[0] = y;
		break;
	case 3: 
		TailX[0] = x;
		TailY[0] = y - 1;
		break;
	}
\

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




