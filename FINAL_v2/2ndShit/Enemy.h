#pragma once


#include "Trash.h"
#include "Bullet.h"
class Enemy
{
	SDL_Rect src, dest;
	static SDL_Texture *tex;

	Trash smeti[10];
	Bullet metk;

	static SDL_Rect tmp;
	static Mix_Chunk *dead;

public:
	static int lvl; // lvl indikator
	bool life; //life indikator
	bool vis;//visible indikator
	int sc; //smeti counter
	bool hit; //ce se je sprozil bullet
	int xpos, ypos; // x in y pos enemya
	int smer, dist, speed;  //za premikanje

	Enemy();
	~Enemy();

	void update();  //posodobim dest rect
	void spawn(); //spawna enemya
	void release(); //sprosti smet
	void set(); //nalozi teksture 
	void move();//premakne x in y pos za random
	void randmove(); //zgenerira random premik
	int random(int min, int max);// funkcija za random
	void render(); //narise enemya na ekran ce je v zonu playerja
	void render_trash();//narise smeti
	void move_trash();//premika smeti
	void check_trash(int x,int y);//preverimo ce je player zadel smeti
	void bullet_start(int x,int y);//sprozi metek
	void check_bullet(); //preveri stanje metka 
	bool check_lvl();//preveri ce so smeti in sam objekt se zivi
	void if_visible(int x, int y);//preverimo ce nas player vidi
	void check_land(int x, int y);
	void set_bullet();
};

