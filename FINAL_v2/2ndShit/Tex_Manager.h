#pragma once
#include"SDL.h"
#include "pch.h"
#include "SDL_image.h"

class Tex_Manager
{
public:
	Tex_Manager();
	~Tex_Manager();
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};

