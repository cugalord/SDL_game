#pragma once
#include"Lplayer.h"
class Player
{
	

	SDL_Rect src,dest;
	SDL_Texture *tex;
	SDL_Texture *ltex;

	

	


public:
	Lplayer land;
	int xpos;
	int ypos;
	bool onLand;

	Player();
	~Player();
	void update();
	void set();
	void move();
	void render();
	void set_pos();
	int get_x();
	int get_y();
	int random(int min, int max);
};

