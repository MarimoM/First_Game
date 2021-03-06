// KursinisDarbas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "Game.h"
using namespace std;

int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	int busena = 0;

	Game *game = nullptr;
	game = new Game();

	//Sukuriam langa
	game->init("Dinosaur Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, false);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		busena = (game->Frame());
		game->update(busena);
		game->render(busena);

		//Limiting the speed
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {SDL_Delay(frameDelay - frameTime);}
	}
	game->clean();

	return 0;
}