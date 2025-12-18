#include "ship.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

Ship::Ship(SDL_Renderer* _renderer) {
	isVulnerable = true;
	prevTime = 0;
	life = 3;
	pos_x = 475;
	pos_y = 525;
	m_ship = IMG_LoadTexture(_renderer, "Vaisseau.png");
	if (!m_ship) {
		SDL_Log("Erreur chargement image: %s", SDL_GetError());
	}
}

void Ship::Render(SDL_Renderer* _renderer) {
	if (m_ship) {
		SDL_FRect rect = {pos_x, pos_y, 80, 80};
		SDL_RenderTexture(_renderer, m_ship, nullptr, &rect);
	}
}

void Ship::Updatehp(float now) {
	if (now - prevTime >= 3) {
		isVulnerable = true;
	}

	if (isVulnerable) {
		life -= 1;
		prevTime = now;
		isVulnerable = false;
	}

	if (!isVulnerable)
		return;
}
