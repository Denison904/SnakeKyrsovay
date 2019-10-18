#pragma once

#include <string>
using namespace std;
struct Data {
	double info[160];
	int rresult;
};

class Neuron {
public:
	double value;
	double error;
	void act();	
};


class NetWork {
public:
	int Layers;
	Neuron** neurons;
	double*** weights;
	int *size;
	int threadsNum = 1;
	double sigm_pro(double x);
	double predict(double x);
	void setLayersNotStudy(int n, int* p, string filename);
	void setLayers(int n, int* p);
	void setRandomInput();
	void setInput(double p[]);
	void show();
	void WeightUpdate(int Start, int Stop, int LayerNum, int lr);
	void ErrorCounter(int LayerNamber, int Start, int Stop, double prediction, double rresult, double lr);
	void LayersCleaner(int LayerNumber, int Start, int Stop);
	void ForwardFeeder(int LayerNumber, int Start, int Stop);
	double ForwardFeed();
	bool SaveWeights();
	void BackPropogation(double pridiction, double rresult, double lr);
};