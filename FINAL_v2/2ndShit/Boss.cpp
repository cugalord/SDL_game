#include "pch.h"
#include <stdlib.h>
#include <time.h>
#include "Tex_Manager.h"
#include "Boss.h"
#include "Trash.h"
#include "Bullet.h"
#include "Map.h"

Boss::Boss()
{
	std::cout << "Boss initialized" << std::endl;
	src.h = 128, src.w = 128;			//DEFINIRAMO W IN H SRC IN DEST RECTA
	dest.h = 128, dest.w = 128;
	src.x = 0, src.y = 0;


	sc = 0; //Smeti counter postavimo na 0
	life = 30;//life indikator postavimo na 30
	hit = 0;



}

void Boss::spawn()
{
	int x = 0;
	int y = 0;
	bool c = 1; // indikator za while zanko

	while (c == 1)
	{
		x = random(0, 770);
		y = random(0, 770);

		if (Map::cmp(x, y) == 1)
		{
			xpos = x;
			ypos = y;
			c = 0;
		}
	};


	randmove();
}



void Boss::update()
{
	if (life == 0)
	{

	}
	else
	{
		dest.x = xpos; // posodobimo lokacijo enemya
		dest.y = ypos;

	}
}

void Boss::set()
{
	tex = Tex_Manager::LoadTexture("boss.png"); //nalozimo teksturo za enemya
		smeti[0].set();
	metk.set();
}

void Boss::render()
{
	if (life >0)
	{

		Tex_Manager::Draw(tex, src, dest); //renderamo enemya
		metk.render();
	}
	else
	{

	}
}
void Boss::render_trash()
{


	for (int i = 0; i <= sc; i++)
	{
		smeti[i].render();
	}


}

void Boss::release()
{

		if (sc < 1000 && Map::cmp(xpos,ypos)==0)
		{
			smeti[sc].spawn((xpos), (ypos - 31));

			sc++;
		}


}



void Boss::move()
{
	if (life >0)
	{
		switch (smer)
		{
		case 1://gor
			if (ypos <= 0 || dist <= 0 || ypos - speed < 0 )
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
			if (ypos >= 770 || dist <= 0 || ypos + speed > 770)
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
			if (xpos <= 0 || dist <= 0 || xpos - speed < 0 )
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
			if (xpos >= 770 || dist <= 0 || xpos + speed > 770)
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

		update(); // POSODOBIMO DEST RECT
		release(); //KLICEMO FUNKCIJO ZA SMETI(PREVERI CE SMO OB OBALI)
	}
	metk.move();


}

void Boss::move_trash()
{
	for (int i = 0; i <= sc; i++)
	{
		smeti[i].move();
	}
}

void Boss::check_trash(int x, int y)  //preveri ce nas je player zadel
{
	for (int i = 0; i <= sc; i++)
	{
		smeti[i].check(x, y);
	}
}


int Boss::random(int min, int max) //funkcija za random
{
	return rand() % (max + 1 - min) + min;
}

void Boss::randmove()
{
	smer = random(1, 4);
	dist = random(10, 80);
	speed = random(3, 3);
}


void Boss::bullet_start(int x, int y)
{
	const Uint8 *keyState;
	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_SPACE] && life >0)
	{

		metk.start(xpos, ypos, x, y);
		hit = 1;
	}
}
void Boss::check_bullet()
{
	if (metk.end() == 1) //preveri stanje metka
	{
		life--;
	}
}


bool Boss::check_lvl() //vrne 1 ce so objekt in vse njegove smeti mrtvi
{
	if (life <30)
	{
		int v = 0;

		for (int i = 0; i < 1000; i++)
		{
			if (smeti[i].get_life() == 0)
			{
				v++;
			}

		}
		if (v >= 1000)
		{
			return 1;
		}
		else
		{
			return 0;
		}

	}
	return 0;
}




Boss::~Boss()
{
	SDL_DestroyTexture(tex); // unicimo teksturo
}
