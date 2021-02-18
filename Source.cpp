#include <iostream>

#include "Game.h"

int main()
{
	srand(static_cast<int>(time(NULL)));
	Game game(800, 600, "Aim Training by @felixjoykind"); // game object

	while (game.GetWindow().isOpen())
	{
		game.update(); // update
		game.render(); // render
	}

	return 0;
}