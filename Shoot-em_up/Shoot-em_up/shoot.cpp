#include "shoot.h"
#include <SDL3_image/SDL_image.h>
#include "ship.h"

Shoot::Shoot(SDL_Renderer* _renderer, Ship& _ship) {
	pos_x = _ship.pos_x + 32;
	pos_y = _ship.pos_y + 5;
	laser = IMG_LoadTexture(_renderer, "laser.png");
	if (!laser) {
		SDL_Log("Erreur chargement image: %s", SDL_GetError());
	}
}

void Shoot::Render(SDL_Renderer* _renderer) {
	if (laser) {
		rect = { pos_x, pos_y, 15, 15 };
		SDL_RenderTexture(_renderer, laser, nullptr, &rect);
	}
}

void Shoot::Update(float dt) {
	pos_y -= 200 * dt;

	rect.x = pos_x;
	rect.y = pos_y;
	rect.w = 15;
	rect.h = 15;
}
