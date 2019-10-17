// Version 0.1.0;
#include "Global.h"
#include "Game.h"



int main() {

	Game game;
	game.Fruit::set();
	game.Draw();
	while (game.getAlive()) {
		game.Input();
		game.Logic();
		game.Draw();
	}

	return 0;
}