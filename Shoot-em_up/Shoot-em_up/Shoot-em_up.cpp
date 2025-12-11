#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "ship.h"
#include "shoot.h"
#include "background.h"
#include "exit.h"
#include "start.h"
#include "move.h"
#include "niveau.h"

void Update(float timePrev, SDL_Renderer* renderer, Ship& ship, Shoot& shoot, Up up) {
    if (timePrev >= 1.0f / 60.0f) {
        ship.Render(renderer);
        shoot.Render(renderer);
        up.Moving(shoot);
    }
}

int main(int argc, char** argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_SetAppMetadata("SDL Test", "1.0", "games.anakata.test-sdl");
    if (!SDL_Init(SDL_INIT_VIDEO))
        return 1;

    if (!SDL_CreateWindowAndRenderer("Shoot'em up", 1024, 768, SDL_WINDOW_RESIZABLE,
        &window, &renderer))
        return 1;

    if (TTF_Init() < 0) {
        SDL_Log("Erreur TTF_Init: %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(renderer, 1024, 768,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);
    Niveau* niveau_1 = new Niveau;
    niveau_1->CreateEnnemy("Niveau_1.txt");
    Niveau* niveau_2 = new Niveau;
    niveau_2->CreateEnnemy("Niveau_2.txt");
    Button* exit = new Exit(renderer);
    Button* start = new Start(renderer);
    Ship ship(renderer);
    Shoot shoot(renderer);
    Up up;
    Down down;
    Right right;
    Left left;
    Background bg(renderer);

    bool gameStart = false;
    bool keepGoing = true;
    float timePrev = 0;
    while (keepGoing) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.button.x;
                float my = event.button.y;
                if (mx >= exit->buttonRect.x && mx <= exit->buttonRect.x + exit->buttonRect.w &&
                    my >= exit->buttonRect.y && my <= exit->buttonRect.y + exit->buttonRect.h) {
                    if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                        exit->Press(renderer);
                        SDL_RenderPresent(renderer);
                        keepGoing = false;
                    }
                }
                if (mx >= start->buttonRect.x && mx <= start->buttonRect.x + start->buttonRect.w &&
                    my >= start->buttonRect.y && my <= start->buttonRect.y + start->buttonRect.h) {
                    if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                        start->Press(renderer);
                        SDL_RenderPresent(renderer);
                        gameStart = true;
                    }
                }
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_Z) {
                    up.Moving(ship);
                }
                if (event.key.key == SDLK_D) {
                    right.Moving(ship);
                }
                if (event.key.key == SDLK_Q) {
                    left.Moving(ship);
                }
                if (event.key.key == SDLK_S) {
                    down.Moving(ship);
                }
            }
        }
        int window_w, window_h;
        SDL_GetWindowSize(window, &window_w, &window_h);
        SDL_RenderClear(renderer);
        bg.Render(renderer, window_w, window_h);

        if (gameStart) {
            float now = SDL_GetTicks();
            float dt = now - timePrev;
            timePrev = now;
            Update(timePrev, renderer, ship, shoot, up);
        }
        else {
            exit->Render(renderer);
            start->Render(renderer);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    delete exit; exit = nullptr;
    delete start; start = nullptr;
    delete niveau_1; niveau_1 = nullptr;
    delete niveau_2; niveau_2 = nullptr;

    return 0;
}