#include "menu.h"
#include "exit.h"
#include "start.h"
#include "pause.h"
#include "play.h"
#include "gameover.h"

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