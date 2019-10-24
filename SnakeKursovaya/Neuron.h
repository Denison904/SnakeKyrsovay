#pragma once
#include <vector>

using namespace std;

struct Neuron
{
	double value;
	double error;
	void act() {
		value = 1 / (1+exp(-value));
	}
};

class NetWork {
public:
	int Layers;
	Neuron** neuron;
	double*** weights;
	int* size;
	double DSigm(double x);
	double predict(double x);
	void setLayers(int n, vector<int> p);
	void setInput(vector<double> p);
	void LayersCleaner(int layerNumber, int start, int stop);
	void ForwardFeeder(int layerNumber, int start, int stop);
	double ForwardFeed();
	void Error(int layerNumber, int start, int stop, double prediction, double rresult, double lr);
	void WeightUpdate(int start, int stop, int layerNumber, int lr);
	void BackPropogation(double prediction, double rresult, double lr);
};