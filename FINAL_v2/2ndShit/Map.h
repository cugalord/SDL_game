#pragma once


class Map
{
	

	SDL_Rect src, dest;
	SDL_Texture *trava;
	SDL_Texture *voda;

public:
	static bool type[24][24];


	Map();
	void set();
	static bool cmp(int x,int y);
	void load_lvl(int lvl);
	void draw();
	~Map();
};

