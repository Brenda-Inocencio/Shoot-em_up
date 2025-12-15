#include "ennemy.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <random>
#include <string>

Ennemy::Ennemy(int _time, int _height, float _speed, int _hp, SDL_Renderer* _renderer) {
	time = _time;
	height = _height;
	speed = _speed;
	hp = _hp;
	pos_x = GetRandomNumber(0, 944);
	pos_y = 0;
	rect = {pos_x, pos_y, 80, 80};

	font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 12);
	if (!font) {
		SDL_Log("Erreur chargement police: %s", SDL_GetError());
	}
	SDL_Color text_color = { 0, 255, 0, 255 };
	textSurface = TTF_RenderText_Solid(font, std::to_string(hp).c_str(), 6, text_color);
	textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_DestroySurface(textSurface);

	if (!textTexture) {
		SDL_Log("Erreur rendu texte: %s", SDL_GetError());
	}
	meteorite = IMG_LoadTexture(_renderer, "meteorite.png");
	if (!meteorite) {
		SDL_Log("Erreur chargement image: %s", SDL_GetError());
	}
}

void Ennemy::Render(SDL_Renderer* _renderer, float _now) {
	if (meteorite) {
		if (time <= _now) {
			SDL_FRect dst = {pos_x, pos_y, 80.0f, 80.0f};
			SDL_RenderTexture(_renderer, meteorite, nullptr, &dst);
			if (textTexture) {
				float tw, th;
				SDL_GetTextureSize(textTexture, &tw, &th);
				SDL_FRect textRect = {pos_x + 30, pos_y + 30, (float)tw, (float)th};
				SDL_RenderTexture(_renderer, textTexture, nullptr, &textRect);
			}
		}
	}
}

int Ennemy::GetRandomNumber(int min, int max) {
	std::random_device m_rd;
	std::mt19937 m_gen(m_rd());

	std::uniform_int_distribution<int> dis(min, max);
	return dis(m_gen);
}

void Ennemy::Update(float dt) {
	pos_y += 40 * speed * dt;

	rect.x = pos_x;
	rect.y = pos_y;
	rect.w = 80.0f;
	rect.h = 80.0f;
}

void Ennemy::UpdateText(SDL_Renderer* _renderer) {
	if (textTexture) SDL_DestroyTexture(textTexture);
	SDL_Color text_color = {0, 255, 0, 255};
	textSurface = TTF_RenderText_Solid(font, std::to_string(hp).c_str(), 6, text_color);
	textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);
	SDL_DestroySurface(textSurface);
}

Ennemy::~Ennemy() {
	TTF_CloseFont(font);
	SDL_DestroyTexture(meteorite);
	SDL_DestroyTexture(textTexture);
}