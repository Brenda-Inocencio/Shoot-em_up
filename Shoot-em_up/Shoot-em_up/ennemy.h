#pragma once
#include "SDL3/SDL.h"

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct TTF_Font;
struct SDL_FRect;

class Ennemy {
	SDL_Texture* meteorite;
	TTF_Font* font;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
public:
	SDL_FRect rect;
	bool isActive;
	float timer;
	int height;
	float speed;
	int hp;
	int defaultHp;
	float pos_x;
	float pos_y;
	Ennemy(float timer, int _height, float _speed, int _hp, SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
	int GetRandomNumber(int min, int max);
	void Update(float now, float dt);
	void UpdateText(SDL_Renderer* _renderer);
	~Ennemy();
};
