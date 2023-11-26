#pragma once
class Lplayer
{
	SDL_Rect src, dest;
	SDL_Texture *tex;


	Mix_Chunk *spa;

	
	SDL_Rect boat;

public:
	int xpos;
	int ypos;
	bool life;


	Lplayer();
	~Lplayer();

	void spawn(int xpos, int ypos);
	void set_tex();
	void move();
	void render();
	bool get_back();
	int get_x();
	int get_y();
};

