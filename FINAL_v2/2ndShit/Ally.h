#pragma once
#include "SDL_mixer.h"

class Ally
{

	SDL_Rect src, dest;
	static SDL_Texture *tex;

public:
	int xpos, ypos; // x in y pos
	int smer, dist, speed;
	bool life; //life indikator
	static SDL_Rect tmp; // tmp rect ki se uporabi v check funkciji
	static Mix_Chunk *ing;


	Ally();
	~Ally();

	void update(); //posodobimo dest rect
	void move(); //dobimo nov random x in y pos
	void randmove();
	int random(int min, int max);
	void render(); //narisemo teksturo
	void set(); //nalozimo teksturo
	void spawn(); //spawnamo smet x in y dobimo od enemya
	void check(int x, int y); //preverimo ce nas je player zadel
	bool get_life(); //vrne status life
};

