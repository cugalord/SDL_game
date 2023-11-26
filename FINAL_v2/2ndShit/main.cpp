#include "SDL.h"
#include "pch.h"
#include "SDL_image.h"
#include "Game.h"
#include <iostream>

Game* game = nullptr;

int main(int argc, char *argv[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;


	game = new Game();

	game->init("Zeleni pirat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 801, 801, false);
	game->set_tex();

	while (game->menu() == 1)
	{
		game->start();
		
	}


	while (game->running()) {

		frameStart = SDL_GetTicks();
		game->chk();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {

			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	return 0;
}