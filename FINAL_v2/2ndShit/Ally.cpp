#include "pch.h"
#include "Ally.h"
#include "SDL_mixer.h"
#include "Tex_Manager.h"


SDL_Rect Ally::tmp;
SDL_Texture* Ally::tex;

Mix_Chunk* Ally::ing;


Ally::Ally()
{
	src.w = 32, src.h = 32; //postavimo w in h rectov
	dest.w = 32, dest.h = 32;
	src.x = 0, src.y = 0;
	dest.x = 0, dest.y = 0;
	tmp.h = 32; tmp.w = 32;
}


void Ally::set()
{
	tex = Tex_Manager::LoadTexture("ally.png"); //Nalozimo teksturo
	ing = Mix_LoadWAV("bim.wav");
	std::cout << Mix_GetError() << std::endl;
}

void Ally::spawn()
{
	life = 1;				//spawnamo smet x in y pozicije dobimo od enemya
	int x = 0;
	int y = 0;
	bool c = 1; // indikator za while zanko

	while (c == 1)
	{
		x = random(0, 770);
		y = random(0, 770);

		if (Map::cmp(x, y) == 0)
		{
			xpos = x;
			ypos = y;
			c = 0;
		}
	};
	randmove();

}
void Ally::update()
{
	dest.x = xpos;       //posodobimo pozicije dest recta
	dest.y = ypos;
}

void Ally::move()
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
			if (ypos >= 770 || dist <= 0 || ypos + speed > 770 || (Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos), (ypos + 31)) == 1))
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
			if (xpos >= 770 || dist <= 0 || xpos + speed > 770 || (Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos + 31), (ypos)) == 1))
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


void Ally::render()
{
	if (life == 1)
	{
		Tex_Manager::Draw(tex, src, dest); //damo teksturo na render
	}
}

void Ally::check(int x, int y) //preverimo ce nas je player zadel
{

	if (life == 1)
	{

		tmp.x = x, tmp.y = y;

		if (SDL_HasIntersection(&dest, &tmp) == 1) //uporabimo funkcijo ki nam vrne ali smo zadeli playerja
		{
			Mix_PlayChannel(2, ing, 0);
			life = 0;
		}
	}

}
void Ally::randmove()
{
	smer = random(1, 4);
	dist = random(10, 100);
	speed = random(2, 2);
}

int Ally::random(int min, int max)
{

	return rand() % (max + 1 - min) + min;
}

bool Ally::get_life()
{
	return life;
}


Ally::~Ally()
{
	SDL_DestroyTexture(tex); // unicimo teksturo
}



