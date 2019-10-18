#include "Neuron.h"
#include "SensorBorder.h"
#include "SensorFood.h"
#include "Global.h"

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

