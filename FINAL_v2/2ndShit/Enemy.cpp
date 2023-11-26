#include "pch.h"
#include <stdlib.h>
#include <time.h>
#include "Tex_Manager.h"
#include "Enemy.h"
#include "Trash.h"
#include "Bullet.h"
#include "Map.h"



SDL_Texture* Enemy::tex;
SDL_Rect Enemy::tmp;
Mix_Chunk* Enemy::dead;


Enemy::Enemy()
{
	std::cout << "Enemy initialized" << std::endl;
	src.h = 32, src.w = 32;			//DEFINIRAMO W IN H SRC IN DEST RECTA
	dest.h = 32, dest.w = 32;
	tmp.w = 32, tmp.h = 32;
	src.x = 0, src.y = 0;


	sc = 0; //Smeti counter postavimo na 0
	vis = 0;
	life = 1;//life indikator postavimo na 1
	hit = 0;



}

void Enemy::spawn()
{
	int x = 0;
	int y=0;
	bool c=1; // indikator za while zanko

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



void Enemy::update()
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

void Enemy::set()
{
	tex = Tex_Manager::LoadTexture("sovraznik.png"); //nalozimo teksturo za enemya
		smeti[0].set();
		dead = Mix_LoadWAV("bam.wav");
	
	metk.set();
}

void Enemy::render()
{
	if (life == 1 && vis==1)
	{

		Tex_Manager::Draw(tex, src, dest); //renderamo enemya
		metk.render();
	}
	else
	{

	}
}
void Enemy::render_trash()
{
	

		for (int i = 0; i <= sc; i++)
		{
			smeti[i].render();
		}
	
	
}

void Enemy::release()
{
	if (Map::cmp((xpos + 32), ypos) == 0) //pogledamo ce smo ob obali in spustimo smet
	{
		if (sc < 10)
		{
			smeti[sc].spawn((xpos + 32), ypos);
			
			sc++;
		}
	}
	else if (Map::cmp((xpos), ypos-32) == 0) //pogledamo ce smo ob obali in spustimo smet
	{
		if (sc < 10)
		{
			smeti[sc].spawn((xpos), (ypos-32));

			sc++;
		}
	}
	else if (Map::cmp((xpos - 32), ypos) == 0) //pogledamo ce smo ob obali in spustimo smet
	{
		if (sc < 10)
		{
			smeti[sc].spawn((xpos - 32), ypos);

			sc++;
		}
	}
	else if (Map::cmp((xpos), (ypos+32)) == 0) //pogledamo ce smo ob obali in spustimo smet
	{
		if (sc < 10)
		{
			smeti[sc].spawn((xpos), (ypos+32));

			sc++;
		}
	}


}



void Enemy::move()
{
	if (life == 1 )
	{
		switch (smer)
		{
		case 1://gor
			if (ypos <= 0 || dist <= 0 || ypos - speed < 0 || (Map::cmp(xpos, ypos-31) == 0 ) || Map::cmp(xpos, ypos) == 0)
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
			if (ypos >= 770 || dist <= 0 || ypos + speed > 770 || (Map::cmp(xpos, ypos+31) == 0) || Map::cmp(xpos, ypos) == 0)
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
			if (xpos <= 0 || dist <= 0 || xpos - speed < 0 || (Map::cmp(xpos-31, ypos) == 0 ) || Map::cmp(xpos, ypos) == 0)
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
			if (xpos >= 770 || dist <= 0 || xpos + speed > 770 || (Map::cmp(xpos+31, ypos) == 0 ) || Map::cmp(xpos, ypos) == 0)
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

void Enemy::move_trash()
{
	for (int i = 0; i <= sc; i++)
	{
		smeti[i].move();
	}
}

void Enemy::check_trash(int x, int y){  //preveri ce nas je player zadel
	for (int i = 0; i <= sc; i++) {
		smeti[i].check(x, y);
	}
}


int Enemy::random(int min, int max) { //funkcija za random
	return rand() % (max + 1 - min) + min;
}

void Enemy::randmove() {
	smer = random(1, 4);
	dist = random(10, 80);
	speed = random(2, 2);
}

void Enemy::if_visible(int x,int y) {
	int
		px = x + 16,
		py = y + 16,
		ex = xpos + 16,
		ey = ypos + 16,
		rangex = abs(px - ex),
		rangey = abs(py - ey);

	if (sqrt(rangex * rangex + rangey * rangey) < 200){
		vis = 1;
	}
	else{
		vis = 0;
	}
}


void Enemy::bullet_start(int x, int y)
{
	const Uint8 *keyState;
	keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_SPACE] && life==1 && vis==1){
		metk.start(xpos, ypos, x, y);
		hit = 1;
	}
}
void Enemy::check_bullet()
{
	if (metk.end() == 1){ //preveri stanje metka
		life = 0;
	}
}


bool Enemy::check_lvl() //vrne 1 ce so objekt in vse njegove smeti mrtvi
{
	if (life == 0){
		int v=0;
		for (int i = 0; i < 10; i++){
			if (smeti[i].get_life() == 0){
				v++;
			}
		}

		if (v >= 10){
			return 1;
		}

		else{
			return 0;
		}

	}

	return 0;
}



void Enemy::set_bullet()
{
	metk.set();
}


void Enemy::check_land(int x, int y)
{
	if (life == 1)
	{

		tmp.x = x;
		tmp.y = y;
		if (SDL_HasIntersection(&dest, &tmp) == 1)
		{
			life = 0;
			Mix_PlayChannel(3, dead, 0);
		}
	}

}


Enemy::~Enemy()
{
	SDL_DestroyTexture(tex); // unicimo teksturo
}
