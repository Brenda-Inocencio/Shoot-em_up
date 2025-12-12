#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "ship.h"
#include "shoot.h"
#include "background.h"
#include "exit.h"
#include "start.h"
#include "pause.h"
#include "play.h"
#include "move.h"
#include "niveau.h"
#include "ennemy.h"

void MenuRenderer(SDL_Renderer* renderer, Button* exit, Button* start) {
    exit->Render(renderer);
    start->Render(renderer);
}

void GameRenderer(SDL_Renderer* renderer, Ship& ship, std::vector<Shoot*> shoots, Niveau* niveau) {
    ship.Render(renderer);
    for (int i = 0; i < shoots.size(); i++) {
        shoots[i]->Render(renderer);
    }
    //for (int i = 0; i < niveau->ennemies.size(); i++) {
    //    niveau->ennemies[i]->Render(renderer);
    //}
}

void Update(float dt, Ship& ship, std::vector<Shoot*> shoots, Up& up, Right& right, Left& left, Down& down, bool isUp, bool isRight, bool isLeft, bool isDown) {
    for (int i = 0; i < shoots.size(); i++) {
        up.Moving(shoots[i], dt);
    }
    if (isUp) {
        up.Moving(ship, dt);
    }
    if (isRight) {
        right.Moving(ship, dt);
    }
    if (isLeft) {
        left.Moving(ship, dt);
    }
    if (isDown) {
        down.Moving(ship, dt);
    }
}

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_SetAppMetadata("SDL Test", "1.0", "games.anakata.test-sdl");
    if (!SDL_Init(SDL_INIT_VIDEO))
        return 1;

    if (!SDL_CreateWindowAndRenderer("Shoot'em up", 1024, 768, 0,
        &window, &renderer))
        return 1;

    if (TTF_Init() < 0) {
        SDL_Log("Erreur TTF_Init: %s", SDL_GetError());
    }

    SDL_SetRenderLogicalPresentation(renderer, 1024, 768,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    Niveau* niveau_1 = new Niveau;
    niveau_1->CreateEnnemy("Niveau_1.txt", renderer);
    Niveau* niveau_2 = new Niveau;
    niveau_2->CreateEnnemy("Niveau_2.txt", renderer);
    Button* exit = new Exit(renderer);
    Button* start = new Start(renderer);
    Button* pause = new Pause(renderer);
    Button* play = new Play(renderer);
    Ship ship(renderer);
    std::vector<Shoot*> shoots;
    Up up;
    Down down;
    Right right;
    Left left;
    Background bg(renderer);

    bool isUp = false;
    bool isRight = false;
    bool isLeft = false;
    bool isDown = false;
    bool gameStart = false;
    bool isPaused = false;
    bool keepGoing = true;
    float timePrev = 0;
    while (keepGoing) {
        float now = float(SDL_GetTicks()) / 1000.0f;
        float dt = now - timePrev;
        timePrev = now;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                keepGoing = false;
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.button.x;
                float my = event.button.y;
                if (isPaused) {
                    if (mx >= exit->buttonRect.x && mx <= exit->buttonRect.x + exit->buttonRect.w &&
                        my >= exit->buttonRect.y && my <= exit->buttonRect.y + exit->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            exit->Press(renderer);
                            SDL_RenderPresent(renderer);
                            isPaused = false;
                            gameStart = false;
                        }
                    }
                    if (mx >= start->buttonRect.x && mx <= start->buttonRect.x + start->buttonRect.w &&
                        my >= start->buttonRect.y && my <= start->buttonRect.y + start->buttonRect.h) {
                        if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                            start->Press(renderer);
                            SDL_RenderPresent(renderer);
                            isPaused = false;
                        }
                    }
                }
                else {
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
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_Z) {
                    isUp = true;
                }
                if (event.key.key == SDLK_D) {
                    isRight = true;
                }
                if (event.key.key == SDLK_Q) {
                    isLeft = true;
                }
                if (event.key.key == SDLK_S) {
                    isDown = true;
                }
                if (event.key.key == SDLK_SPACE) {
                    Shoot* shoot = new Shoot(renderer, ship);
                    shoots.push_back(shoot);
                }
                if (event.key.key == SDLK_ESCAPE) {
                    isPaused = true;
                }
            }
            if (event.type == SDL_EVENT_KEY_UP) {
                if (event.key.key == SDLK_Z) {
                    isUp = false;
                }
                if (event.key.key == SDLK_D) {
                    isRight = false;
                }
                if (event.key.key == SDLK_Q) {
                    isLeft = false;
                }
                if (event.key.key == SDLK_S) {
                    isDown = false;
                }
            }
        }
        int window_w, window_h;
        SDL_GetWindowSize(window, &window_w, &window_h);
        SDL_RenderClear(renderer);
        bg.Render(renderer, window_w, window_h);

        if (isPaused) {
            bg.Render(renderer, window_w, window_h);
            pause->Render(renderer);
            play->Render(renderer);
        }
        else if (gameStart) {
            Update(dt, ship, shoots, up, right, left, down, isUp, isRight, isLeft, isDown);
            GameRenderer(renderer, ship, shoots, niveau_1);
        }
        else if (!isPaused && !gameStart) {
            MenuRenderer(renderer, exit, start);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    delete exit; exit = nullptr;
    delete start; start = nullptr;
    delete pause; pause = nullptr;
    delete play; play = nullptr;
    delete niveau_1; niveau_1 = nullptr;
    delete niveau_2; niveau_2 = nullptr;
    for (Shoot* s : shoots) {
        delete s; s = nullptr;
    }
    shoots.clear();
    return 0;
}
