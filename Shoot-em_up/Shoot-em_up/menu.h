#pragma once

struct SDL_Renderer;
class Button;

class Menu {
public:
	Menu();
	void MenuRenderer(SDL_Renderer* renderer, Button* exit, Button* start);
	void MenuPauseRenderer(SDL_Renderer* renderer, Button* pause, Button* play);
	void MenuGameOverRenderer(SDL_Renderer* renderer, Button* gameOver);
	void MenuWinRenderer(SDL_Renderer* renderer, Button* win, Button* play);
};