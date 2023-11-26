#include "pch.h"
#include "Tex_Manager.h"
#include "Lplayer.h"


Lplayer::Lplayer()
{
	src.w = 32, src.h = 32;
	dest.w = 32, dest.h = 32;
	boat.h = 32, boat.w = 32;
	src.x = 0, src.y = 0;
	dest.x = 0, dest.y = 0;
	xpos = 0, ypos = 0;
	life = 0;
}

void Lplayer::set_tex()
{
	tex = Tex_Manager::LoadTexture("landP.png");
	spa=Mix_LoadWAV("land.wav");
}

void Lplayer::spawn(int x,int y)
{
	Mix_PlayChannel(2, spa, 0);
	
	xpos = x;
	ypos = y;
	dest.x = x;
	dest.y = y;
	life = 1;
	move();

	boat.x = x;
	boat.y = y;

}

void Lplayer::move()
{
	if (life == 1)
	{
		const Uint8 *keyState;

		keyState = SDL_GetKeyboardState(NULL);  //premiokamo playerja uporabimo cmp fnk za hitboxe
		if (keyState[SDL_SCANCODE_RIGHT])
		{
			if (xpos >= 770)
			{
				std::cout << "corner" << std::endl;
			}
			else
			{
				if (Map::cmp(xpos, ypos) == 0 || Map::cmp((xpos + 31), (ypos)) == 0)
				{
					std::cout << "HIT" << std::endl;
				}
				else
				{
					xpos = xpos + 3;
				}
			}
		}
		else if (keyState[SDL_SCANCODE_LEFT])
		{
			if (xpos <= 0)
			{
				std::cout << "corner" << std::endl;
			}
			else
			{
				if (Map::cmp(xpos, ypos) == 0 || Map::cmp((xpos - 31), (ypos)) == 0)
				{
					std::cout << "HIT" << std::endl;
				}
				else
				{
					xpos = xpos - 3;
				}
			}
		}
		else if (keyState[SDL_SCANCODE_DOWN])
		{
			if (ypos >= 770)
			{
				std::cout << "corner" << std::endl;
			}
			else
			{
				if (Map::cmp(xpos, ypos) == 0 || Map::cmp((xpos), (ypos + 31)) == 0)
				{
					std::cout << "HIT" << std::endl;
				}
				else
				{
					ypos = ypos + 3;
				}
			}
		}
		else if (keyState[SDL_SCANCODE_UP])
		{
			if (ypos <= 0)
			{
				std::cout << "corner" << std::endl;
			}
			else
			{
				if (Map::cmp(xpos, ypos) == 0 || Map::cmp((xpos), (ypos - 31)) == 0)
				{
					std::cout << "HIT" << std::endl;
				}
				else
				{
					ypos = ypos - 3;
				}
			}
		}
		dest.x = xpos;
		dest.y = ypos;
	}
}



bool Lplayer::get_back()
{
	if (SDL_HasIntersection(&dest, &boat) == 1)
	{
		const Uint8 *keyState;

		keyState = SDL_GetKeyboardState(NULL);
		if (keyState[SDL_SCANCODE_B])
		{
			life = 0;
			dest.x = 0;
			dest.y = 0;
			xpos = 0;
			ypos = 0;
			return 1;
		}
		else
		{
			return 0;
		}

	}
	else
	{
		return 0;
	}
}

int Lplayer::get_x()
{
	if (life == 1)
	{
		return xpos;
	}
	else
	{
		return 800;
	}
}

int Lplayer::get_y()
{
	if (life == 1)
	{
		return ypos;
	}
	else
	{
		return 800;
	}
}

void Lplayer::render()
{
		Tex_Manager::Draw(tex, src, dest);
}


Lplayer::~Lplayer()
{
	SDL_DestroyTexture(tex);
}
