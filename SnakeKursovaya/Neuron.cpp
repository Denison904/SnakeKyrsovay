#include "Neuron.h"
#include "Global.h"
#include <ctime>
#include <random>


double NetWork::DSigm(double x) {
	if (fabs(x-1)<1e-9||fabs(x)<1e-9)
	{
		return 0.0;
	}
	return x * (1.0 - x);
}

double NetWork::predict(double x) {
	if (x > 0.8) return 1;
	else return 0;
}

void NetWork::setLayers(int n, vector<int> p) {
	srand(time(0));
	Layers = n;
	neuron = new Neuron * [n];
	weights = new double** [n - 1];
	size = new int[n];
	for (int i = 0; i < n; i++)
	{
		size[i] = p[i];
		neuron[i] = new Neuron[p[i]];
		if (i < n - 1) {
			weights[i] = new double* [p[i]];
			for (int  j = 0; j < p[i]; j++)
			{
				weights[i][j] = new double[p[i + 1]];
				for (int k = 0; k < p[i+1]; k++)
				{
					weights[i][j][k] = (rand() % 100) * 0.01 / size[i];
				}
			}
		}
	}
}

void NetWork::setInput(vector<double> p) {
	for (int i = 0; i < size[0]; i++)
	{
		neuron[0][i].value = p[i];
	}
}

void NetWork::ForwardFeeder(int layerNumber, int start, int stop) {
	for (int j = start; j < stop; j++)
	{
		for (int  k = 0; k < size[layerNumber-1]; k++)
		{
			neuron[layerNumber][j].value += neuron[layerNumber][k].value * weights[layerNumber - 1][k][j];
		}
	}
}

void NetWork::LayersCleaner(int layerNumber, int start, int stop) {
	for (int i = start; i < stop; i++)
	{
		neuron[layerNumber][i].value = 0;
	}
}

double NetWork::ForwardFeed() {
	for (int i = 0; i < Layers; i++)
	{
		LayersCleaner(i, 0, size[i]);
	}
	double max = 0;
	double prediction = 0;
	for (int  i = 0; i < size[Layers-1]; i++)
	{
		if (neuron[Layers - 1][i].value > max)
		{
			max = neuron[Layers - 1][i].value;
			prediction = 1;
		}
	}
	return prediction;
}

void NetWork::Error(int layerNumber, int start, int stop, double prediction, double rresult, double lr) {
	if (layerNumber==Layers-1)
	{
		for (int j = start; j < stop; j++)
		{
			if (j!= int(rresult))
			{
				neuron[layerNumber][j].error = -pow(neuron[layerNumber][j].value, 2);
			}
			else
			{
				neuron[layerNumber][j].error = 1.0 - neuron[layerNumber][j].value;
			}
		}
	}
	else
	{
		for (int j = start; j < stop; j++)
		{
			double error = 0.0;
			for (int k = 0; k < size[layerNumber]; k++)
			{
				error += neuron[layerNumber + 1][k].value * weights[layerNumber][j][k];
			}
			neuron[layerNumber][j].error = error;
		}
		
	}
}

void NetWork::WeightUpdate(int start, int stop, int layerNumber, int lr) {
	int i = layerNumber;
	for (int j = start; j < stop; j++)
	{
		for (int  k = 0; k < size[i+1]; k++)
		{
			weights[i][j][k] += lr * neuron[i + 1][k].error * DSigm(neuron[i + 1][k].value) * neuron[i][j].error;
		}
	}
}

void NetWork::BackPropogation(double prediction, double rresult, double lr) {
	for (int i = Layers - 1; i > 0; i--) {
		if (i == Layers-1)
		{
			for (int j = 0; j < size[i]; j++)
			{
				if (j != int(rresult)) {
					neuron[i][j].error = -pow(neuron[i][j].value, 2);
				}
				else
				{
					neuron[i][j].error = 1.0 - neuron[i][j].value;
				}
			}
		}
		else
		{
			for (int j = 0; j < size[i]; j++)
			{
				double error = 0.0;
				for (int  k = 0; k < size[i+1]; k++)
				{
					error += neuron[i + 1][k].error * weights[i][j][k];
				}
				neuron[i][j].error = error;
			}
		}
	}
	
}