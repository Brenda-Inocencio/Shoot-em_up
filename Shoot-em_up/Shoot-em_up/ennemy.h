
#pragma once

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct TTF_Font;

class Ennemy {
	int time;
	int nb;
	int height;
	float speed;
	int hp;
	SDL_Texture* meteorite;
	TTF_Font* font;
	SDL_Surface* textSurface;
	SDL_Texture* textTexture;
public:
	float pos_x;
	float pos_y;
	Ennemy();
	Ennemy(int _time, int _nb, int _height, float _speed, int _hp, SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer);
	int GetRandomNumber(int min, int max);
};
