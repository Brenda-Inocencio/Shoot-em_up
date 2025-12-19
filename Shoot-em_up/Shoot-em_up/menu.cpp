#include "menu.h"
#include "button.h"
#include "win.h"

Menu::Menu() {
}

void Menu::MenuRenderer(SDL_Renderer* renderer, Button* exit, Button* start) {
    exit->Render(renderer);
    start->Render(renderer);
}

void Menu::MenuPauseRenderer(SDL_Renderer* renderer, Button* pause, Button* play) {
    pause->Render(renderer);
    play->Render(renderer);
}

void Menu::MenuGameOverRenderer(SDL_Renderer* renderer, Button* gameOver) {
    gameOver->Render(renderer);
}

void Menu::MenuWinRenderer(SDL_Renderer* renderer, Win* win, Button* exit) {
    win->Render(renderer);
    win->End(renderer);
    exit->Render(renderer);
}

void Menu::MenuNextLevelRenderer(SDL_Renderer* renderer, Win* win, Button* play) {
    win->Render(renderer);
    win->NextLevel(renderer);
    play->Render(renderer);
}