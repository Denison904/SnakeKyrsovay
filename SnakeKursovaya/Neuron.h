#pragma once
#include <vector>
#include "Game.h"

using namespace std;
class InPut
{
public:
	double value;
	double* weights;
	double error;
};

class HL
{
public:
	double value;
	double* weights;
	double error;
	double w0;
};

class OutPut
{	
public:
	double value;
	double error;
	double w0;
};

class NetWork {
public:
	NetWork(int x);
	Game *game;
	vector<vector<int>> tmpinput;
	vector<double> tmpoutput[4];
	vector<int> RightResult[4];
	InPut *input;
	OutPut *output;
	HL **hl;
	double learningR = 1;
	int Layer = 7;
	int size[7] = {11*11*2, 11*11*8,11*11*8,248,121,11, 4};
	double act(double x);
	double Dsigm(double x);
	void setLayers();
	void Input(int* x);
	void ForwardFeed();
	void BackPropogation(double *rr, double *testAnswer);
	int max();
};