#include "shoot.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Shoot::Shoot(SDL_Renderer* _renderer) {
	pos_x = 475;
	pos_y = 525;
	laser = IMG_LoadTexture(_renderer, "laser.png");
	if (!laser) {
		SDL_Log("Erreur chargement image: %s", SDL_GetError());
	}
}

void Shoot::Render(SDL_Renderer* _renderer) {
	if (laser) {
		SDL_FRect rect = { pos_x, pos_y - 10, 200, 200 };
		SDL_RenderTexture(_renderer, laser, nullptr, &rect);
	}
}
