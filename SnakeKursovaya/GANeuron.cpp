#include "GANeuron.h"

GA::GA() {
	ga = new Game[11*11*2];

	srand(time_t(0));
	input = new GAInput[size[0]];
	for (int i = 0; i < size[0]; i++)
	{
		input[i].weights = new double[size[1]];
		for (int j = 0; j < size[1]; j++)
		{
			input[i].weights[j] = rand() % 100 * 0.01 - 0.5;
		}
	}
	output = new GAOutput[size[Layer - 1]];
}

void GA::ForwardWeed() {
	for (int i = 0; i < size[Layer-1]; i++)
	{
		double arg = 0;
		for (int j = 0; j < size[0]; j++)
		{
			arg += input[j].weights[i] * input[j].value;
		}
		output[i].value = act(arg);
	}
	max();
}


void GA::Input(int *in) {
	
}

double GA::act(double x) {
	return 1 / (1 + exp(-x));
}

int GA::max() {
	double max = output[0].value;
	int k = 0;
	for (int i = 1; i < size[Layer-1]; i++)
	{
		if (output[i].value>max)
		{
			k = i;
			max = output[i].value;
		}
	}
	return k;
}