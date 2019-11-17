#pragma once
#include "Game.h"


class GAInput{
public:
	double value;
	double* weights;
};

class GAHL {
	double value;
	double* weights;
	double w0;
};

class GAOutput {
public:
	double value;
	double w0;
};

class GA
{
public:
	GA();

	int* sourse;
	int population = 100;
	Game *ga;	
	const int Layer = 2;
	int size[2] = { 11 * 11 * 2-1, 4 };
	GAInput* input;
	//GAHL* hl;
	GAOutput* output;
	void setLayerFirst() ;
	void setLayer();
	void Input(int *in);
	void ForwardWeed();
	double act(double x);
	int max();
};
