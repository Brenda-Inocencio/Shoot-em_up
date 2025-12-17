#pragma once

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Score {
	SDL_Surface* textSurface;
	SDL_Surface* scoreSurface;
	SDL_Texture* textTexture;
	SDL_Texture* scoreTexture;
public :
	int score;
	Score(SDL_Renderer* renderer);
	void UpdateScore();
	void Render(SDL_Renderer* renderer);
};

