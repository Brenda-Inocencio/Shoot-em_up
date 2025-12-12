#pragma once

struct SDL_Texture;
struct SDL_Renderer;
class Ship;

class Shoot {
public:
	float pos_x;
	float pos_y;
	SDL_Texture* laser;
	Shoot(SDL_Renderer* _renderer, Ship& _ship);
	void Render(SDL_Renderer* _renderer);
};