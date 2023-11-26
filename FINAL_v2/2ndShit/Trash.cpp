#include "pch.h"
#include <time.h>
#include <stdlib.h>
#include "SDL_Mixer.h"
#include "Trash.h"
#include "Tex_Manager.h"


SDL_Rect Trash::tmp;
SDL_Texture* Trash::tex;

Mix_Chunk* Trash::ding;

Trash::Trash()
{
	src.w = 32, src.h = 32; //postavimo w in h rectov
	dest.w = 32, dest.h = 32;
	src.x = 0, src.y = 0;
	dest.x = 0,dest.y = 0;

	tmp.h = 32; tmp.w = 32;
}


void Trash::set()
{
	tex = Tex_Manager::LoadTexture("trash.png"); //Nalozimo teksturo
	ding=Mix_LoadWAV("ding.wav");
}

void Trash::spawn(int x,int y)
{
	life = 1;				//spawnamo smet x in y pozicije dobimo od enemya
	xpos = x, ypos = y;
	randmove();
	
}
void Trash::update()
{
	dest.x = xpos;       //posodobimo pozicije dest recta
	dest.y = ypos;
}

void Trash::move()
{

	if (life == 1)
	{
		switch (smer)
		{
		case 1://gor
			if (ypos <= 0 || dist <= 0 || ypos - speed < 0 || (Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos), (ypos - 31)) == 1))
			{
				randmove();
			}
			else
			{
				ypos -= speed;
				dist -= speed;
			}
			break;

		case 2: //dol
			if (ypos >= 770 || dist <= 0 || ypos + speed > 770 ||(Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos), (ypos + 31)) == 1))
			{
				randmove();
			}
			else
			{
				ypos += speed;
				dist -= speed;
			}
			break;

		case 3: //levo
			if (xpos <= 0 || dist <= 0 || xpos - speed < 0 || (Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos - 31), (ypos)) == 1))
			{
				randmove();
			}
			else
			{
				xpos -= speed;
				dist -= speed;
			}
			break;

		case 4: //desno
			if (xpos >= 770 || dist <= 0 || xpos + speed > 770 ||( Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos + 31), (ypos)) == 1))
			{
				randmove();
			}
			else
			{
				xpos += speed;
				dist -= speed;
			}
			break;
		};

			update();
		}
	}


void Trash::render()
{
	if (life == 1)
	{
		Tex_Manager::Draw(tex, src, dest); //damo teksturo na render
	}
}

void Trash::check(int x, int y) //preverimo ce nas je player zadel
{

	if (life == 1)
	{

		tmp.x = x, tmp.y = y;

		if (SDL_HasIntersection(&dest, &tmp) == 1) //uporabimo funkcijo ki nam vrne ali smo zadeli playerja
		{
			Mix_PlayChannel(5,ding, 0);
			life = 0;
		}
	}
	
}
void Trash::randmove()
{
	smer = random(1, 4);
	dist = random(10, 100);
	speed = random(1, 1);
}

int Trash::random(int min, int max)
{
	
	return rand() % (max + 1 - min) + min;
}

bool Trash::get_life()
{
	return life;
}


Trash::~Trash()
{
	SDL_DestroyTexture(tex); // unicimo teksturo
}
