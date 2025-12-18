#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class Ship {
public:
	bool isVulnerable;
	float prevTime;
	int life;
	float pos_x;
	float pos_y;
	SDL_Texture* m_ship;
	Ship(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
	void Updatehp(float now);
};
