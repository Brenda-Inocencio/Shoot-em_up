#pragma once

struct SDL_Texture;
struct SDL_Surface;
struct SDL_Renderer;
struct TTF_Font;

class Ship {
public:
	bool isVulnerable;
	float prevTime;
	int life;
	float pos_x;
	float pos_y;
	SDL_Texture* m_ship;
	SDL_Texture* heart;
	SDL_Texture* textHeartTexture;
	SDL_Surface* textHeartSurface;
	TTF_Font* font;
	Ship(SDL_Renderer* _renderer);
	~Ship();
	void Render(SDL_Renderer* _renderer);
	void Updatehp(SDL_Renderer* _renderer, float now);
};
