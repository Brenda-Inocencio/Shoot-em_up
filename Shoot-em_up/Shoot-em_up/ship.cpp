#include "ship.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

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
	heart = IMG_LoadTexture(_renderer, "heart.png");
	if (!heart) {
		SDL_Log("Erreur chargement image: %s", SDL_GetError());
	}
	font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 12);
	if (!font) {
		SDL_Log("Erreur chargement police: %s", SDL_GetError());
	}
	SDL_Color text_color = {255, 255, 255, 255};
	textHeartSurface = TTF_RenderText_Solid(font, std::to_string(life).c_str(), 1, text_color);
	textHeartTexture = SDL_CreateTextureFromSurface(_renderer, textHeartSurface);
}

Ship::~Ship() {
	SDL_DestroyTexture(m_ship);
	SDL_DestroyTexture(heart);
	SDL_DestroyTexture(textHeartTexture);
	SDL_DestroySurface(textHeartSurface);
}

void Ship::Render(SDL_Renderer* _renderer) {
	if (m_ship) {
		SDL_FRect rect = {pos_x, pos_y, 80, 80};
		SDL_RenderTexture(_renderer, m_ship, nullptr, &rect);
	}
	if (heart) {
		SDL_FRect rect = {10, 700, 50, 50};
		SDL_RenderTexture(_renderer, heart, nullptr, &rect);
	}
	if (textHeartTexture) {
		float tw, th;
		SDL_GetTextureSize(textHeartTexture, &tw, &th);
		SDL_FRect textRect = {30, 715, (float)tw, (float)th};
		SDL_RenderTexture(_renderer, textHeartTexture, nullptr, &textRect);
	}
}

void Ship::Updatehp(SDL_Renderer* _renderer, float now) {
	if (now - prevTime >= 3) {
		isVulnerable = true;
	}

	if (isVulnerable) {
		life -= 1;
		prevTime = now;
		isVulnerable = false;
		if (textHeartTexture) SDL_DestroyTexture(textHeartTexture);
		SDL_Color text_color = {255, 255, 255, 255};
		textHeartSurface = TTF_RenderText_Solid(font, std::to_string(life).c_str(), 6, text_color);
		textHeartTexture = SDL_CreateTextureFromSurface(_renderer, textHeartSurface);
	}

	if (!isVulnerable)
		return;
}