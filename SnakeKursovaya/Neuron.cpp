#include "Neuron.h"
#include "SensorBorder.h"
#include "SensorFood.h"
#include "Global.h"
#include <ctime>
#include <random>

void Neuron::act() {
	value = 1 / (1 + exp(-value));
}

bool NetWork::SaveWeights() {
	fstream fout;
	fout.open("weights.txt");
	for (int i = 0; i < Layers; i++)
	{
		if (i < Layers - 1) {
			for (int j = 0; j < size[i]; j++)
			{
				for (int k = 0; k < size[i+1]; k++)
				{
					fout << weights[i][j][k]<<" ";
				}
			}
		}
	}
	fout.close();
	return 1;
}


double NetWork::sigm_pro(double x) {
	if (fabs(x - 1) < 1e-9 || fabs(x) < 1e-9) return 0;
	double res = x * (1.0 - x);
	return res;
}

double NetWork::predict(double x) {
	if (x = 0.9) return 1;
	else return 0;
}

void NetWork::setLayersNotStudy(int n, int* p, string filename) {
	ifstream fin;
	fin.open(filename);
	srand(time(0));
	neurons = new Neuron * [n];
	weights = new double** [n - 1];
	size = new int[n];
	for (int  i = 0; i < n; i++)
	{
		size[i] = p[i];
		neurons[i] = new Neuron[p[i]];
		if (i<n-1)
		{
			weights[i] = new double* [p[i]];
			for (int j = 0; j < p[i]; j++)
			{
				weights[i][j] = new double[p[i + 1]];
				for (int k = 0; k < p[i+1]; k++)
				{
					fin >> weights[i][j][k];
				}
			}
		}
	}
}

void NetWork::setLayers(int n, int* p) {
	srand(time(0));
	Layers = n;
	neurons = new Neuron * [n];
	weights = new double** [n - 1];
	size = new int[n];
	for (int  i = 0; i < n; i++)
	{
		size[i] = p[i];
		neurons[i] = new Neuron[p[i]];
		if (i < n - 1) {
			weights[i] = new double* [p[i]];
			for (int j = 0; j < p[i]; j++)
			{
				weights[i][j] = new double[p[i + 1]];
				for (int  k = 0; k < p[i+1]; k++)
				{
					weights[i][j][k] = (rand() % 100) * 0.01 / size[i];
				}
			}
			
		}
	}

}

void NetWork::setRandomInput() {
	for (int i = 0; i < size[0]; i++)
	{
		neurons[0][i].value = rand() % 100 * 0.01;
	}
}

void NetWork::setInput(double p[]) {
	for (int  i = 0; i < size[0]; i++)
	{
		neurons[0][i].value = p[i];
	}
}

void NetWork::LayersCleaner(int LayerNumber, int Start, int Stop) {
	srand(time(0));
	for (int i = Start; i < Stop; i++) {
		neurons[LayerNumber][i].value = 0;
	}
}

void NetWork::ForwardFeeder(int LayerNumber, int Start, int Stop) {
	for (int j = 0; j < Stop; j++)
	{
		for (int k = 0; k < size[LayerNumber-1]; k++)
		{
			neurons[LayerNumber][j].value += neurons[LayerNumber - 1][k].value * weights[LayerNumber][k][j];
		}
		neurons[LayerNumber][j].act();
	}
}

double NetWork::ForwardFeed() {
	setlocale(LC_ALL, "ru");
	for (int i = 1; i < Layers; i++)
	{
		NetWork::LayersCleaner(i, 0, int(floor(size[i] / 2)));
		NetWork::ForwardFeeder(i, 0, size[i]);
	}
	double max = 0;
	double prediction = 0;
	for (int i = 0; i < size[Layers-1]; i++)
	{
	//	cout << char(i + 65) << " : " << neurons[Layers - 1][i].value << endl;
		if (neurons[Layers - 1][i].value > max) {
			max = neurons[Layers - 1][i].value;
			prediction = i;
		}
	}
	return prediction;
}

void NetWork::ErrorCounter(int LayerNumber, int Start, int Stop, double prediction, double rresult, double lr) {
	if (LayerNumber == Layers - 1) {
		for (int  j = Start; j < Stop; j++)
		{
			if (j != int(rresult)) {
				neurons[LayerNumber][j].error = -pow(neurons[LayerNumber][j].value, 2);
			}
			else
			{
				neurons[LayerNumber][j].error = pow(1.0 - neurons[LayerNumber][j].value, 2);
			}
		}
	}
	else
	{
		for (int j = Start; j < Stop; j++)
		{
			double error = 0.0;
			for (int k = 0; k < size[LayerNumber + 1]; k++) {
				error += neurons[LayerNumber + 1][k].error * weights[LayerNumber][j][k];
			}
			neurons[LayerNumber][j].error = error;
		}
	}
}

void NetWork::WeightUpdate(int Start, int Stop, int LayerNum, int lr) {
	int i = LayerNum;
	for (int  j = Start	; j < Stop; j++)
	{
		for (int  k = 0; k < size[i+1]; k++)
		{
			weights[i][j][k] += lr * neurons[i + 1][k].error * sigm_pro(neurons[i + 1][k].value * neurons[i][j].value);
		}
	}
}

void NetWork::BackPropogation(double prediction, double rresult, double lr) {
	for (int i = Layers-1; i >0; i--)
	{
		if (i == Layers - 1) {
			for (int j = 0; j < size[i]; j++) {
				if (j != int(rresult)) {
					neurons[i][j].error = -pow((neurons[i][j].value), 2);
				}
				else {
					neurons[i][j].error = pow(1.0 - neurons[i][j].value, 2);
				}

			}
		}
		else {
			for (int j = 0; j < size[i]; j++) {
				double error = 0.0;
				for (int k = 0; k < size[i + 1]; k++) {
					error += neurons[i + 1][k].error * weights[i][j][k];
				}
				neurons[i][j].error = error;
			}
		}
	}
	for (int i = 0; i < Layers-1; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			for (int k = 0; k < size[i+1]; k++)
			{
				weights[i][j][k] += lr * neurons[i + 1][k].error * sigm_pro(neurons[i + 1][k].value) * neurons[i][j].value;
			}
		}
	}
}