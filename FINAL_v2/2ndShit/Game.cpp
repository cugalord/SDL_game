#include "Game.h"
#include "SDL_mixer.h"
#include "Tex_Manager.h"
#include "Player.h"
#include "Map.h"
#include "pch.h"
#include <iostream>
#include "Enemy.h"
#include "Ally.h"
#include "Boss.h"




Game::~Game() {}
Game::Game()
{
}


SDL_Renderer* Game::renderer = nullptr;


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fulscreen) {
	int flags = 0;
	isPlaying = 0;
	isspawn = 0;
	p = 0;

	if (fulscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { //preverimo ce se vse pravilno inicializira

		std::cout << "Subsystems Initialized" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) {
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer) {
			//SDL_SetRenderDrawColor(renderer, 0XFF, 0, 0xFF, 0xFF);
			std::cout << "Renderer created" << std::endl;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << Mix_GetError() << std::endl;
		}

		song = Mix_LoadMUS("song.mp3"); //nalozimo mp3 file 
		fin = Mix_LoadMUS("iron.mp3");
		en = Mix_LoadMUS("snoop.mp3");
		up = Mix_LoadWAV("up.wav");
		std::cout << Mix_GetError() << std::endl;
		Mix_PlayMusic(song, -1);
		ac = 0;
		isEnd = 0;
		isMenu = 1;
		
	}

	else {
		isMenu = 0;
	}

}


void Game::start()
{
	SDL_RenderClear(renderer);
	Tex_Manager::Draw(mtex,msrc,mdest);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		if (event.type == SDL_QUIT)
		{
			isMenu = 0;
			isRunning = 0;
		}

		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//If the left mouse button was pressed
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				//Get the mouse offsets
				int x = event.button.x;
				int y = event.button.y;

				//If the mouse is over the button
				if ((x > 135) && (x < 135 + 355) && (y > 403) && (y < 403+95))
				{
					isRunning = 1;
					isMenu = 0;
					SDL_DestroyTexture(mtex);
				}
				else
				{

				}
			}
		}
		else
		{

		}
	}



	
}


void Game::set_tex() // nalozimo vse teksture in spawnamo sovraznike
{
	player.set();
	map.set();
	bos.set();
	map.load_lvl(1);
	player.set_pos();
	isFinal = 0;
	lvl = 1;
	enc = 5;
	ac = 2;
	zav[0].set();
	enemy[0].set();

	for (int i = 0; i < 30; i++)
	{
		enemy[i].set_bullet();
	}

	for (int i = 0; i < enc; i++)
	{
		enemy[i].spawn();
	}

	for (int i = 0; i < ac; i++)
	{
		zav[i].spawn();
	}


	mtex = Tex_Manager::LoadTexture("ozadje.png");
	msrc.w = 800, msrc.h = 800;
	msrc.x = 0, msrc.y = 0;
	mdest.w = 800, mdest.h = 800;
	mdest.x = 0, mdest.y = 0;


	ftex = Tex_Manager::LoadTexture("final.png");
	fsrc.w = 800, fsrc.h = 800;
	fsrc.x = 0, fsrc.y = 0;
	fdest.w = 800, fdest.h = 800;
	fdest.x = 0, fdest.y = 0;

	etex = Tex_Manager::LoadTexture("over.png");
	esrc.w = 800, esrc.h = 800;
	esrc.x = 0, esrc.y = 0;
	edest.w = 800, edest.h = 800;
	edest.x = 0, edest.y = 0;

}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT: //Igra se ustavi
		isRunning = false;
		break;
	}



}
void Game::chk()
{
	int tmp=0;

	if (isspawn == 0)
	{
		for (int i = 0; i < enc; i++)
		{
			if (enemy[i].check_lvl() == 1)
			{
				tmp++;
			}
		}
		if (tmp >= enc)
		{
			lvl++;
			Mix_PlayChannel(3, up, 0);
			set(lvl);
		}
	}

	else
	{
		if (bos.check_lvl() == 1)
		{
			lvl++;
			isPlaying = 0;
			set(lvl);
			
		}
	}
}

void Game::set(int lvl)
{
	map.load_lvl(lvl);
	
	switch (lvl) {
	case 1:
		enc = 5;
		break;
	case 2:
		enc = 15;
		ac = 3;
		break;
	case 3:
		enc = 30;
		ac = 5;
		break;
	case 4:
		enc = 0;
		isFinal = 1;
		break;
	case 5:
		enc = 0;
		isFinal = 0;
		break;
	case 6:
		enc = 0;
		isFinal = 0;
		isEnd = 1;
		isspawn = 0;
		p = 0;
	}

	spawn();

}

void Game::spawn()
{
	if (p == 0)
	{
		player.set_pos();
	}

	for (int i = 0; i < enc; i++)
	{
		enemy[i].spawn();
	}

	for (int i = 0; i < ac; i++)
	{
		zav[i].spawn();
	}

	if (lvl == 4)
	{
		if (isPlaying == 0)
		{
			Mix_HaltMusic();
			Mix_PlayMusic(fin,-1);
			isPlaying = 1;
		}


		while (isFinal == 1)
		{
			final();
		}
	}

	if (lvl == 5)
	{
		if (isspawn == 0)
		{
			bos.spawn();
			p = 1;
			isspawn = 1;
		}
		
	}

	if (lvl == 6)
	{
		
		if (isPlaying == 0)
		{
			Mix_HaltMusic();
			Mix_PlayMusic(en, -1);
			isPlaying = 1;
		}

		while (isEnd == 1)
		{
			end();
		}
	}
}

void Game::update() //premaknemo objekte in preverimo collision-e
{
	player.move();


	for (int i = 0; i < enc; i++)
	{
		enemy[i].move();
		enemy[i].move_trash();
		enemy[i].check_trash(player.xpos, player.ypos);
		enemy[i].if_visible(player.get_x(),player.get_y());
		enemy[i].bullet_start(player.xpos, player.ypos);
		enemy[i].check_land(player.land.get_x(), player.land.get_y());
		enemy[i].check_bullet();
	}


	for (int i = 0; i < ac; i++)
	{
		zav[i].move();
		zav[i].check(player.xpos,player.ypos);
	}


	if (isspawn == 1)
	{	
		bos.move();
		bos.move_trash();
		bos.check_trash(player.xpos, player.ypos);
		bos.bullet_start(player.xpos, player.ypos);
		bos.check_bullet();
	}

}
void Game::final()
{
	SDL_RenderClear(renderer);
	Tex_Manager::Draw(ftex, fsrc, fdest);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		if (event.type == SDL_QUIT)
		{
			isMenu = 0;
			isRunning = 0;
		}

		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//If the left mouse button was pressed
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				//Get the mouse offsets
				int x = event.button.x;
				int y = event.button.y;

				//If the mouse is over the button
				if ((x > 186) && (x < 186 + 460) && (y > 435) && (y < 435 + 189))
				{
					isFinal = 0;
					lvl=5;
					SDL_DestroyTexture(ftex);
				}
				else
				{

				}
			}
		}
		else
		{

		}
	}
}

void Game::render() { //damo teksture na renderer in ga presentamo
	SDL_RenderClear(renderer);
	map.draw();
	player.render();


	for (int i = 0; i < enc; i++)
	{
		enemy[i].render();
		enemy[i].render_trash();
	}


	for (int i = 0; i < ac; i++)
	{
		zav[i].render();
	}

	if (isspawn == 1)
	{
		bos.render();
		bos.render_trash();
	}

	SDL_RenderPresent(renderer);

}

void Game::end()
{
	SDL_RenderClear(renderer);
	Tex_Manager::Draw(etex, esrc, edest);
	SDL_RenderPresent(renderer);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		if (event.type == SDL_QUIT)
		{
			isMenu = 0;
			isRunning = 0;
		}

		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			//If the left mouse button was pressed
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				//Get the mouse offsets
				int x = event.button.x;
				int y = event.button.y;

				//If the mouse is over the button
				if ((x > 135) && (x < 135 + 355) && (y > 403) && (y < 403 + 95))
				{
					isFinal = 0;
					isRunning = 0;
					SDL_DestroyTexture(etex);
					clean();
				}
				else
				{

				}
			}
		}
		else
		{

		}
	}



}

void Game::clean() { //unicimo renderer in window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);


	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}