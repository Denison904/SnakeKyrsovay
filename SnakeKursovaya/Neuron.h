#pragma once

#include <string>
using namespace std;
struct date {
	double info[160];
	int rresult;
};

class Neuron {
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
	void LayersCleaner(int LayerNumber, int start, int stop);
	void ForwardFeeder(int LayerNumber, int start, int stop);
	double ForwardFeed();
	double ForwardFeed(string program);
	bool SaveWeights();
};