#include "Global.h"
#include "Fruit.h"
#include<ctime>

using namespace std;

void Fruit::set() { 
	srand(static_cast<unsigned int>(time(0)));
	x = rand() % (width - 2) + 1;
	y = rand() % (high - 2) + 1;
}