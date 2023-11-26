#include "pch.h"
#include "Tex_Manager.h"
#include "SDL.h"
#include "SDL_image.h"


Tex_Manager::Tex_Manager()
{
	
}


Tex_Manager::~Tex_Manager()
{
}


void Tex_Manager::Draw(SDL_Texture * tex, SDL_Rect src, SDL_Rect dest) {

	SDL_RenderCopy(Game::renderer, tex, &src, &dest); //dodamo tekstureo na renderer
}

SDL_Texture* Tex_Manager::LoadTexture(const char* texture) {

	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface); //ustvarimo texksturo iz surfaca kateremu naložimo sliko
	SDL_FreeSurface(tempSurface);


	return tex;

}