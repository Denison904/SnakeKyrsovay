// Version 0.1.0;
#include "Global.h"
#include "Game.h"



int main() {
	cout << "Enter h(human) or a(artificial intelligence): ";
	Game game;
	game.Draw();
	
	while (game.getAlive()) {
		game.Input();
		game.Logic();
		game.Draw();
	}

	return 0;
}