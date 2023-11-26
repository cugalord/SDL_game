#include "pch.h"
#include "Map.h"
#include "Tex_Manager.h"
#include <time.h>
#include <stdlib.h>

bool Map::type[24][24];

Map::Map()
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			type[i][j] = 0;						//postavimo vrednosti na 0 
		}

	}
	
	src.h = 32, src.w = 32;  //dolocimo W in H src in destb rectu
	dest.h = 32, dest.w = 32;
	src.x = 0 , src.y = 0;
	dest.x = 0, dest.y = 0;

}
void Map::set()
{
    trava=Tex_Manager::LoadTexture("grass.png");  //nalozimo teksture
	voda=Tex_Manager::LoadTexture("water.png");
}




void Map::draw()
{


	for (int i = 0; i < 25; i++)  //narisemo mapo
	{
		for (int j = 0; j < 25; j++)
		{
			dest.x = j * 32;
			dest.y = i * 32;

			switch (type[i][j]) {

			case 0:
				Tex_Manager::Draw(voda, src, dest);
				break;

			case 1:
				Tex_Manager::Draw(trava, src, dest);
				break;

			default:
				Tex_Manager::Draw(voda, src, dest);
				break;

			};

		}

		
	}
}


void Map::load_lvl(int lvl) 
{

	switch (lvl) {

	case 1:
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				type[i][j] = 1;

			}
		}


		for (int i = 8; i < 12; i++)
		{
			for (int j = 8; j < 12; j++)
			{
				type[i][j] = 1;

			}
		}

		break;

	case 2:

		for (int i = 3; i < 20;i++)
		{
			for (int j = 5; j < 20; j++)
			{
				type[i][j] = 1;
			}
		}
		for (int i = 20; i < 24; i++)
		{
			for (int j = 5; j < 9; j++)
			{
				type[i][j] = 1;
			}
		}
		for (int i = 18; i < 24; i++)
		{
			for (int j = 5; j < 9; j++)
			{
				type[i][j] = 1;
			}
		}
		break;

	case 3:
		for (int i = 2; i < 5; i++)
		{
			for (int j = 5; j < 9; j++)
			{
				type[i][j] = 1;
			}
		}
		for (int i = 10; i < 14; i++)
		{
			for (int j = 8; j < 10; j++)
			{
				type[i][j] = 1;
			}
		}
		for (int i = 19; i < 23; i++)
		{
			for (int j = 15; j < 19; j++)
			{
				type[i][j] = 1;
			}
		}
		break;
	case 5:
		for (int i = 3; i < 20; i++)
		{
			for (int j = 5; j < 20; j++)
			{
				type[i][j] = 1;
			}
		}

		break;
	}
}

bool Map::cmp(int x, int y) //compare fnk za hitboxe
{
	int x2 = x + 31;
	int y2 = y + 31;

	x = x / 32;
	x2 = x2 / 32;
	y = y / 32;
	y2 = y2 / 32;

	if (type[y][x] == 1 || type[y2][x2] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


	Map::~Map()
{
	SDL_DestroyTexture(trava);
	SDL_DestroyTexture(voda);
}
