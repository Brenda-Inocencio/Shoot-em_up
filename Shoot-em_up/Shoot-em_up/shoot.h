#pragma once
#include <SDL3/SDL.h>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_FRect;
class Ship;

class Shoot {
public:
	float prevtime;
	bool isShoot;
	float pos_x;
	float pos_y;
	SDL_FRect rect;
	SDL_Texture* laser;
	Shoot(SDL_Renderer* _renderer, Ship& _ship);
	void Render(SDL_Renderer* _renderer);
	void Update(float dt);
};
