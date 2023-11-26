#pragma once
class Bullet
{
	SDL_Rect src, dest;
	 SDL_Texture *tex;

	 Mix_Chunk *boom;
	 Mix_Chunk *bam;

public:
	int life;
	SDL_Rect t;
	bool pb;
	int xpos, ypos;

	void start(int x,int y, int px, int py);
	void set();
	void move();
	void update();
	void render();
	bool end();
	Bullet();
	~Bullet();
};

