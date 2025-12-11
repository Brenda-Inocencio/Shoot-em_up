#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class Shoot {
public:
	int pos_x;
	int pos_y;
	SDL_Texture* laser;
	Shoot(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
};