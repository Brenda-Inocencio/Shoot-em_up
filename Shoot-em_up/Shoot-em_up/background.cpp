#include "background.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Background::Background(SDL_Renderer* _renderer) {
	texture = IMG_LoadTexture(_renderer, "espace.png");
	if (!texture) {
		SDL_Log("Erreur chargement image: %s", SDL_GetError());
	}
}

Background::~Background() {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
}

void Background::Render(SDL_Renderer* _renderer) {
	if (texture) {
		SDL_FRect rect = { 0, 0, 1024, 768 };
		SDL_RenderTexture(_renderer, texture, nullptr, &rect);
	}
}