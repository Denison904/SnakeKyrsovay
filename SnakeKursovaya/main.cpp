// Version 0.1.0;
#include "Neuron.h"
#include "GANeuron.h"
#include <iostream>

void main() {
	int iter;
	cout << "Enter how many snake stady:\n";
	cin >> iter;
	NetWork nw;
	while (iter>0)
	{
		
		
		nw.game.Draw();

		while (nw.game.getAlive()) {
			nw.game.Input();
			nw.game.Logic();
			nw.game.Draw();
		}
		iter--;
	}
	
}