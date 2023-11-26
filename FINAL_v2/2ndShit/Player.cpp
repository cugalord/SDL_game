#include "pch.h"
#include "SDL.h"
#include <iostream>
#include "Tex_Manager.h"
#include "Player.h"
#include "Map.h"





Player::Player()
{
	std::cout << "Player initialized" << std::endl; //postavimo w in h za src in dest rect
	src.h = 32, src.w = 32;
	dest.h = 32,dest.w = 32;
	src.x = 0 , src.y = 0;
	onLand = 0;
	
	
}

void Player::set()
{
	tex = Tex_Manager::LoadTexture("igralec.png"); //nalozimo teksturo
	ltex = Tex_Manager::LoadTexture("wait.png");
	land.set_tex();
	
}

void Player::set_pos()
{
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
}

int Player::random(int min, int max) //funkcija za random
{
	return rand() % (max + 1 - min) + min;
}


void Player::update() //posodobimo dest x in y
{

	dest.x = xpos;
	dest.y = ypos;
}

void Player::render()
{
	if (onLand == 0)
	{
		Tex_Manager::Draw(tex, src, dest); //damo teksturo na renderer
		std::cout << SDL_GetError() << std::endl;
	}
	else if (onLand == 1)
	{
		land.render();
		Tex_Manager::Draw(ltex, src, dest);
	}
	
}

void Player::move() 
{


	if (onLand == 0)
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
				if (Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos + 31), (ypos)) == 1)
				{
					std::cout << "HIT" << std::endl;
					if (keyState[SDL_SCANCODE_V])
					{
						land.spawn(xpos+32, ypos);
						onLand = 1;
					}
				}
				else
				{
					xpos = xpos + 4;
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
				if (Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos - 31), (ypos)) == 1)
				{
					std::cout << "HIT" << std::endl;

					if (keyState[SDL_SCANCODE_V])
					{
						land.spawn(xpos-32, ypos);
						onLand = 1;
					}
				}
				else
				{
					xpos = xpos - 4;
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
				if (Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos), (ypos + 31)) == 1)
				{
					std::cout << "HIT" << std::endl;

					if (keyState[SDL_SCANCODE_V])
					{
						land.spawn(xpos, ypos+32);
						onLand = 1;
					}
				}
				else
				{
					ypos = ypos + 4;
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
				if (Map::cmp(xpos, ypos) == 1 && Map::cmp((xpos), (ypos - 31)) == 1)
				{
					std::cout << "HIT" << std::endl;

					if (keyState[SDL_SCANCODE_V])
					{	
						std::cout << xpos << " " << ypos << std::endl;
						land.spawn(xpos, ypos-32);
						onLand = 1;
					}
				}
				else
				{
					ypos = ypos - 4;
				}
			}
		}
	}
	if (onLand == 1)
	{
		land.move();

		if (land.get_back() == 1)
		{
			onLand = 0;
		}
	}
	
	 //std::cout << "player xpos: " << xpos << ", player ypos: " << ypos << std::endl;
	 update();
}

int Player::get_x()
{
	if (onLand == 1)
	{
		return land.get_x();
	}
	else
	{
		return xpos;
	}
}


int Player::get_y()
{
	if (onLand == 1)
	{
		return land.get_y();
	}
	else
	{
		return ypos;
	}
}


Player::~Player()
{
	SDL_DestroyTexture(tex);
	SDL_DestroyTexture(ltex);
}
