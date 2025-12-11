#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class Background {
public:
	SDL_Texture* texture;

	Background();
	~Background();
	Background(SDL_Renderer* _renderer);
	void Render(SDL_Renderer* _renderer, int _window_w, int _window_h);
};
