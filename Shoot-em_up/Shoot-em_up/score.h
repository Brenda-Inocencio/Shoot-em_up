#pragma once

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
struct TTF_Font;

class Score {
	SDL_Surface* textSurface;
	SDL_Surface* scoreSurface;
	SDL_Texture* textTexture;
	SDL_Texture* scoreTexture;
	TTF_Font* font;
public:
	int score;
	Score(SDL_Renderer* renderer);
	void UpdateScore(SDL_Renderer* renderer);
	void Render(SDL_Renderer* renderer);
};
