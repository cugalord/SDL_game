#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include "pch.h"
#include "Player.h"
#include "Map.h"
#include "SDL_image.h"
#include <stdio.h>
#include <iostream>
#include "Enemy.h"
#include "Ally.h"
#include "Boss.h"

class Game {
private:
	int lvl; //lvl counter
	int enc; //enemy counter
	int ac;
	bool isRunning; //nam pove ce je igra prizgana
	bool isMenu; //nam pove ce je meni vzgan
	bool isFinal;//meni za final bossa
	bool isEnd;// ce smo v exit meniju

	bool isPlaying; //ce se igra glasba
	bool isspawn;//ce je boss spawnan
	bool p;//ce je player spawnan

	SDL_Window *window;

	SDL_Texture *mtex; //meni tekstura
	SDL_Texture *ftex; //boss screen tekstura
	SDL_Texture *etex; //exit screen tekstura

	SDL_Rect msrc, mdest;//meni  tekstura
	SDL_Rect fsrc, fdest;//boss screen tekstura
	SDL_Rect esrc, edest;//exit screen tekstura
	
	Mix_Music *song; //game theme song
	Mix_Music *fin;//boss fight song
	Mix_Music *en; //final screen song
	Mix_Chunk *up;//lvl up sound

	//objects
	Player player;
	Map map;
	Enemy enemy[30];
	Ally zav[5];
	Boss bos;

public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fulscreen);

	void handleEvents();
	void update(); 
	void render();
	void clean();
	void set_tex();
	void set(int lvl);
	void chk();
	void spawn();

	void start();//start
	void final();
	void end();

	bool menu() { return isMenu; }
	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
};
