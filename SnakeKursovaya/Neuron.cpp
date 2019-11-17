#include "Neuron.h"
#include "Global.h"
#include <ctime>
#include <random>

NetWork::NetWork(int x) {
	game = new Game[x];
}

double NetWork::act(double x) {
	return x = 1.0 / (1 + exp(-x));
}

double NetWork::Dsigm(double x) {
	
	return act(x) * (1.0 - act(x));
}

void NetWork::Input(int* x) {
	for (int i = 0; i < size[0]; i++)
	{
		input[i].value = x[i];
	}

}

void NetWork::setLayers() {
	srand(static_cast<unsigned int>(time(0)));
	
	input = new InPut[size[0]];
	output = new OutPut[size[Layer - 1]];
	hl = new HL*[Layer-2];
	for (int i = 0; i < size[0]; i++)
	{
		input[i].weights = new double[size[1]];
		for (int j = 0; j < size[1]; j++)
		{
			input[i].weights[j] = ((rand() % 200) - 100) * 0.01;
		}
	}

	for (int i = 0; i < Layer-2; i++)
	{
		hl[i] = new HL[size[i + 1]];
		for (int j = 0; j < size[i+1]; j++)
		{ 
			hl[i][j].weights = new double[size[i+2]];
			for (int k = 0; k < size[i+2]; k++)
			{
				hl[i][j].weights[k] = ((rand() % 200) - 100) * 0.01;
			}
			hl[i][j].w0 = rand() % (int(2 * (0.7 * powf(11*11, 1.0 / 11*11)) + 0.5)) - int((0.7 * powf(11*11, 1.0 / 11*11)) + 0.5);
		}
	}

	
	for (int  i = 0; i < size[Layer-1]; i++)
	{
		output[i].w0 = rand() % (int(2 * (0.7 * powf(11*11, 1.0 / 11*11)) + 0.5)) - int((0.7 * powf(11*11, 1.0 / 11*11)) + 0.5);
	}
}
int NetWork::max() {
	int k = 0;
	double max = output[0].value;
	for (int i = 1; i < 4; i++)
		if (max < output[i].value) {
			max = output[i].value;
			k = i;
		}
	return k;
}

void NetWork::ForwardFeed() {
	for (int i = 0; i < size[1]; i++)
	{
		double arg =  hl[0][i].w0;
		for (int j = 0; j < size[0]; j++)
		{
			arg += input[j].value * input[j].weights[i];
		}
		hl[0][i].value = act(arg);
	}
	for (int i = 0; i < Layer - 3; i++)
	{
		for (int j = 0; j < size[i + 2]; j++)
		{
			double arg =  hl[i][j].w0;
			for (int k = 0; k < size[i + 1]; k++)
			{
				arg += hl[i][k].value * hl[i][k].weights[j];
			}
			hl[i + 1][j].value = act(arg);
		}
	}

	for (int i = 0; i < size[Layer - 1]; i++)
	{
		double arg =   output[i].w0;
		for (int j = 0; j < size[Layer - 2]; j++)
		{
			arg += hl[Layer - 3][j].value * hl[Layer - 3][j].weights[i];
		}
		output[i].value = act(arg);
	}


}

void NetWork::BackPropogation(double *rr, double *testAnswer) {
	for (int i = 0; i < size[Layer - 1]; i++)
	{
		double arg = 0;
		for (int j = 0; j < size[Layer - 2]; j++)
		{
			arg += hl[Layer - 3][j].value * hl[Layer - 3][j].weights[i];
		}
		output[i].error = (rr - testAnswer) * Dsigm(arg);
	}

	for (int j = 0; j < size[Layer - 2]; j++)
	{
		hl[Layer - 3][j].error = 0;
		double arg = 0;
		for (int k = 0; k < size[Layer - 1]; k++)
		{
			hl[Layer - 3][j].error += output[k].error * hl[Layer - 3][j].weights[k];
		}
		for (int k = 0; k < size[Layer - 3]; k++)
		{
			arg += hl[Layer - 4][k].value * hl[Layer - 4][k].weights[j];
		}
		hl[Layer - 3][j].error = Dsigm(arg) * hl[Layer - 3][j].error;
	}

	for (int i = Layer - 4; i > 0; i--)
	{
		for (int j = 0; j < size[i + 1]; j++)
		{
			hl[i][j].error = 0;
			for (int k = 0; k < size[i + 2]; k++)
			{
				hl[i][j].error += hl[i + 1][k].error * hl[i][j].weights[k];
			}
			double arg = 0;
			for (int k = 0; k < size[i]; k++)
			{
				arg += hl[i - 1][k].value * hl[i - 1][k].weights[j];
			}
			hl[i][j].error = hl[i][j].error * Dsigm(arg);
		}
	}
	for (int j = 0; j < size[1]; j++)
	{
		hl[0][j].error = 0;
		for (int k = 0; k < size[2]; k++)
		{
			hl[0][j].error += hl[1][k].error * hl[0][j].weights[k];
		}
		double arg = 0;
		for (int k = 0; k < size[0]; k++)
		{
			arg += input[k].value * input[k].weights[j];
		}
		hl[0][j].error = hl[0][j].error * Dsigm(arg);
	}
	/*for (int i = 0; i < size[0]; i++)
	{
		input[i].error = 0;
		for (int j = 0; j < size[1]; j++)
		{
			input[i].error += hl[0][j].error * input[i].weights[j];
		}
	}*/

	double*** dw;
	dw = new double** [Layer - 1];


	for (int i = 0; i < Layer - 1; i++)
	{
		dw[i] = new double* [size[i]];
		for (int j = 0; j < size[i]; j++)
		{
			dw[i][j] = new double[size[i + 1]];
		}
	}

	for (int j = 0; j < size[0]; j++)
	{
		for (int k = 0; k < size[1]; k++)
		{
			dw[0][j][k] = input[j].value * hl[0][k].error;
			input[j].weights[k] += dw[0][j][k];
		}
	}

	for (int i = 1; i < Layer - 2; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			for (int k = 0; k < size[i + 1]; k++)
			{
				dw[i][j][k] = hl[i - 1][j].value * hl[i][k].error;
				hl[i - 1][j].weights[k] += dw[i][j][k];
			}
			hl[i - 1][j].w0 = hl[i - 1][j].error * learningR;
		}
	}

	for (int j = 0; j < size[Layer - 2]; j++)
	{
		for (int k = 0; k < size[Layer - 1]; k++)
		{
			dw[Layer - 2][j][k] = output[k].error * hl[Layer - 3][j].value;
			hl[Layer - 3][j].weights[k] += dw[Layer - 2][j][k];
		}
		hl[Layer - 3][j].w0 = learningR * hl[Layer - 3][j].error;
	}

	for (int i = 0; i < size[Layer-1]; i++)
	{
		output[i].w0 = output[i].error;
	}



	for (int i = 0; i < Layer - 1; i++)
	{
		for (int j = 0; j < size[i]; j++)
		{
			delete[] dw[i][j];
		}
		delete[] dw[i];
	}
	delete[] dw;


}


