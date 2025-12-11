#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class Ship {
public:
	int pos_x;
	int pos_y;
	SDL_Texture* m_ship;
	Ship(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
};