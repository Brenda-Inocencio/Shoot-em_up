#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "score.h"
#include "ship.h"
#include "shoot.h"
#include "background.h"
#include "exit.h"
#include "start.h"
#include "pause.h"
#include "play.h"
#include "gameover.h"
#include "win.h"
#include "move.h"
#include "niveau.h"
#include "ennemy.h"
#include "menu.h"

void Collisions(SDL_Renderer* renderer, std::vector<Shoot*>& shoots, 
    std::vector<Ennemy*>& ennemies, Ship& ship, float gameTime, Score* score, bool& isGameOver,
    bool& isWin) {
    shoots.erase(
        std::remove_if(
            shoots.begin(), shoots.end(), [&](Shoot* s) {

                // projectile hors écran
                float sx = s->pos_x;
                float sy = s->pos_y;
                if (sy < 0) {
                    delete s;
                    return true; //retire le projectile
                }

                // Collision avec un ennemi
                for (auto& e : ennemies)
                {
                    if (!e->isActive)
                        continue;

                    if (sx >= e->pos_x + 8 && sx <= e->pos_x + 72 &&
                        sy >= e->pos_y && sy <= e->pos_y + 80 ||
                        sx + 15 >= e->pos_x + 8 && sx + 15 <= e->pos_x + 72 &&
                        sy >= e->pos_y && sy <= e->pos_y + 80) 
                    {
                        e->hp -= 2;
                        e->UpdateText(renderer);
                        delete s;
                        return true;
                    }

                }
                return false; // garde le projectile
            }
        ),
        shoots.end()
    );

    //vérifie si l'ennemi meurt et le detruit si c est le cas
    ennemies.erase(
        std::remove_if(
            ennemies.begin(), ennemies.end(), [&](Ennemy* e) {
                if (e->pos_y > 668) {
                    delete e;
                    return true; 
                }
                if (e->hp <= 0) {
                    score->UpdateScore(renderer);
                    delete e;
                    return true;
                }
                return false;
            }
        ),
        ennemies.end()
    );
    if (ennemies.empty()) {
        isWin = true;
    }

    float shipx = ship.pos_x;
    float shipy = ship.pos_y;
    for (auto& e : ennemies)
    {
        if (!e->isActive)
            continue;

        if (e->pos_x + 8 >= shipx && e->pos_x + 8 <= shipx + 80 &&
            shipy >= e->pos_y && shipy <= e->pos_y + 68 ||
            e->pos_x + 72 >= shipx && e->pos_x + 72 <= shipx + 80 &&
            shipy >= e->pos_y && shipy <= e->pos_y + 68) {
            ship.Updatehp(gameTime);
            if (ship.life <= 0) {
                isGameOver = true;
            }
        }
    }
}

void GameRenderer(SDL_Renderer* renderer, Ship& ship, std::vector<Shoot*>& shoots, 
    Niveau* niveau) {
    ship.Render(renderer);
    for (Shoot* s : shoots)
        s->Render(renderer);

    for (Ennemy* e : niveau->ennemies) {
        e->Render(renderer);
    }
}

void Update(float dt, Ship& ship, std::vector<Shoot*>& shoots, Niveau* niveau ,Up& up, 
    Right& right, Left& left, Down& down, bool isUp, bool isRight, bool isLeft, bool isDown,
    float gameTime, float& shootCooldown, bool& canShoot) {

    if (gameTime - shootCooldown >= 0.25f) {
        canShoot = true;
    }
    if (canShoot) {
        shootCooldown = gameTime;
    }

    for (Ennemy* e : niveau->ennemies) {
        e->Update(gameTime, dt);
    }
    for (Shoot* s : shoots)
        s->Update(dt);
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

    if (!SDL_SetRenderVSync(renderer, 1)) {
        SDL_Log("Impossible d'activer le VSync : %s", SDL_GetError());
    }

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
    Button* gameOver = new GameOver(renderer);
    Button* win = new Win(renderer);
    Score* score = new Score(renderer);
    Ship ship(renderer);
    std::vector<Shoot*> shoots;
    Up up;
    Down down;
    Right right;
    Left left;
    Menu menu;
    Background bg(renderer);

    bool isUp = false;
    bool isRight = false;
    bool isLeft = false;
    bool isDown = false;
    bool isGameOver = false;
    bool isWin = false;
    bool gameStart = false;
    bool isPaused = false;
    bool isLvl1 = true;
    bool keepGoing = true;
    float timePrev = 0;
    float timeStart = 0;
    float gameTime = 0;
    float shootCooldown = 0;
    bool canShoot = true;
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
                else if (isWin && mx >= start->buttonRect.x && mx <= start->buttonRect.x + start->buttonRect.w &&
                    my >= start->buttonRect.y && my <= start->buttonRect.y + start->buttonRect.h) {
                    if (event.type != SDL_EVENT_MOUSE_BUTTON_UP) {
                        start->Press(renderer);
                        SDL_RenderPresent(renderer);
                        isWin = false;
                        isLvl1= false;
                        timeStart = now;
                    }
                }
                else if (!gameStart) {
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
                            timeStart = now;
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
                    if (canShoot) {
                        Shoot* shoot = new Shoot(renderer, ship);
                        shoots.push_back(shoot);
                        canShoot = false;
                    }
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

        if (isWin) {
            bg.Render(renderer, window_w, window_h);
            menu.MenuWinRenderer(renderer, win, play);
            score->Render(renderer);
        }
        else if (isGameOver) {
            bg.Render(renderer, window_w, window_h);
            menu.MenuGameOverRenderer(renderer, gameOver);
            score->Render(renderer);
            gameStart = false;
        }
        else if (isPaused) {
            bg.Render(renderer, window_w, window_h);
            menu.MenuPauseRenderer(renderer, pause, play);
        }
        else if (gameStart) {
            gameTime = now - timeStart;
            if (isLvl1) {
                Update(dt, ship, shoots, niveau_1, up, right, left, down, isUp,
                    isRight, isLeft, isDown, gameTime, shootCooldown, canShoot);
                Collisions(renderer, shoots, niveau_1->ennemies, ship, gameTime, score,
                    isGameOver, isWin);
                GameRenderer(renderer, ship, shoots, niveau_1);
            }
            else {
                Update(dt, ship, shoots, niveau_2, up, right, left, down, isUp,
                    isRight, isLeft, isDown, gameTime, shootCooldown, canShoot);
                Collisions(renderer, shoots, niveau_2->ennemies, ship, gameTime, score,
                    isGameOver, isWin);
                GameRenderer(renderer, ship, shoots, niveau_2);
            }
        }
        else {
            menu.MenuRenderer(renderer, exit, start);
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
    delete gameOver; gameOver = nullptr;
    delete win; win = nullptr;
    delete score; score = nullptr;
    delete niveau_1; niveau_1 = nullptr;
    delete niveau_2; niveau_2 = nullptr;
    shoots.clear();
    return 0;
}

