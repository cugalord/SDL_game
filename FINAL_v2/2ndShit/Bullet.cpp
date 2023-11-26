#include "pch.h"
#include "Bullet.h"
#include "Tex_Manager.h"
#include "SDL_mixer.h"





Bullet::Bullet()
{
	src.w = 8, src.h = 8;
	dest.w = 8, dest.h = 8;
	src.x = 0,src.y = 0;
	life = 0;
	pb = 0;
	xpos = 100, ypos = 100;
	t.x = 800, t.y = 800;
	t.w = 32, t.h = 32;

	

	std::cout << "Bullet initialized" << std::endl;
}

void Bullet::set()
{
	tex=Tex_Manager::LoadTexture("bullet.png");
	std::cout << "Bullet texture set" << std::endl;
	boom = Mix_LoadWAV("boom.wav");
	bam = Mix_LoadWAV("bam.wav");
}



void Bullet::start(int x,int y, int px,int py)
{

	life = 1;
	if (life == 1)
	{
		
		xpos = px;
		ypos = py;
		t.x = x;
		t.y = y;
		Mix_PlayChannel(1, boom, 0);
		move();
		
	}
}


void Bullet::move()
{
	if (life == 1)
	{
		if (t.x > xpos && t.y>ypos)
		{
			xpos = xpos + 6;
			ypos = ypos + 6;
		}
		else if (t.x < xpos && t.y < ypos)
		{
			xpos = xpos - 6;
			ypos = ypos - 6;
		}
		else if (t.x > xpos && t.y < ypos)
		{
			xpos = xpos + 6;
			ypos = ypos - 6;
		}
		else if (t.x < xpos && t.y > ypos)
		{
			xpos = xpos - 6;
			ypos = ypos + 6;
		}
		else if (t.x == xpos && t.y > ypos)
		{
			ypos = ypos + 6;
		}
		else if (t.x == xpos && t.y < ypos)
		{
			
			ypos = ypos - 6;
		}
		else if (t.x > xpos && t.y == ypos)
		{
			xpos = xpos + 6;
			
		}
		else if (t.x < xpos && t.y == ypos)
		{
			xpos = xpos - 6;

		}

		update();
		end();

	}
}
void Bullet::update()
{
	dest.x = xpos;
	dest.y = ypos;
}

void Bullet::render()
{
	if (life == 1)
	{
		Tex_Manager::Draw(tex, src, dest);
	}
}


bool Bullet::end()
{
	if (SDL_HasIntersection(&dest,&t)==1)
	{
		life = 0;
		if (pb == 0)
		{
			Mix_PlayChannel(2, bam, 0);
			pb = 1;
		}
		return 1;
	}
	return 0;
}



Bullet::~Bullet()
{
	SDL_DestroyTexture(tex);
}
