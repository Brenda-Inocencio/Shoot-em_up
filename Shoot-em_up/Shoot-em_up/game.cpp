#include "game.h"
#include <vector>
#include "score.h"
#include "ship.h"
#include "shoot.h"
#include "move.h"
#include "level.h"
#include "ennemy.h"

void Game::Collisions(SDL_Renderer* renderer, std::vector<Shoot*>& shoots,
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

                    if (e->height == 1) {
                        if (sx >= e->pos_x + 4 && sx <= e->pos_x + 76 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80 ||
                            sx + 15 >= e->pos_x + 4 && sx + 15 <= e->pos_x + 76 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80) {

                            e->hp -= 2;
                            e->UpdateText(renderer);
                            delete s;
                            return true;
                        }
                    }
                    else if (e->height == 2) {
                        if (sx >= e->pos_x + 6 && sx <= e->pos_x + 74 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80 ||
                            sx + 15 >= e->pos_x + 6 && sx + 15 <= e->pos_x + 74 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80) {

                            e->hp -= 2;
                            e->UpdateText(renderer);
                            delete s;
                            return true;
                        }
                    }
                    else if (e->height == 3) {
                        if (sx >= e->pos_x + 8 && sx <= e->pos_x + 72 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80 ||
                            sx + 15 >= e->pos_x + 8 && sx + 15 <= e->pos_x + 72 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80) {

                            e->hp -= 2;
                            e->UpdateText(renderer);
                            delete s;
                            return true;
                        }
                    }
                    else if (e->height == 4) {
                        if (sx >= e->pos_x + 10 && sx <= e->pos_x + 70 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80 ||
                            sx + 15 >= e->pos_x + 10 && sx + 15 <= e->pos_x + 70 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80) {

                            e->hp -= 2;
                            e->UpdateText(renderer);
                            delete s;
                            return true;
                        }
                    }
                    else if (e->height == 5) {
                        if (sx >= e->pos_x + 12 && sx <= e->pos_x + 68 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80 ||
                            sx + 15 >= e->pos_x + 12 && sx + 15 <= e->pos_x + 68 &&
                            sy >= e->pos_y && sy <= e->pos_y + 80) {

                            e->hp -= 2;
                            e->UpdateText(renderer);
                            delete s;
                            return true;
                        }
                    }
                }
                return false; // garde le projectile
            }
        ),
        shoots.end()
    );

    std::vector<Ennemy*> toAdd;
    //vérifie si l'ennemi meurt et le detruit si c est le cas
    ennemies.erase(
        std::remove_if(
            ennemies.begin(), ennemies.end(), [&](Ennemy* e) {

                if (e->hp <= 0) {
                    score->UpdateScore(renderer);
                    float newPos_x = e->pos_x;
                    float newPos_y = e->pos_y;
                    if (e->height > 1) {
                        int newHeight = e->height - 1;
                        int newHp = std::max(1, e->defaultHp / 2);
                        for (int i = 0; i < 2; i++) {
                            Ennemy* ennemy = new Ennemy(e->timer, newHeight, e->speed, newHp, renderer);
                            if (newPos_x - 20 < 0 || newPos_x + 20 >= 944) {
                                ennemy->pos_x = newPos_x;
                            }
                            else if (i == 0) {
                                ennemy->pos_x = newPos_x - 20;
                            }
                            else {
                                ennemy->pos_x = newPos_x + 20;
                            }
                            ennemy->pos_y = newPos_y - 10;
                            toAdd.push_back(ennemy);
                        }
                    }
                    delete e;
                    return true;
                }
                else if (e->pos_y > 668) {
                    delete e;
                    return true;
                }
                return false;
            }
        ),
        ennemies.end()
    );
    for (auto* e : toAdd)
        ennemies.push_back(e);
    if (ennemies.empty()) {
        isWin = true;
    }

    float shipx = ship.pos_x;
    float shipy = ship.pos_y;
    for (auto& e : ennemies) {

        if (!e->isActive)
            continue;

        if (e->height == 1) {
            if (shipx >= e->pos_x + 4 && shipx <= e->pos_x + 76 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80 ||
                shipx + 15 >= e->pos_x + 4 && shipx + 15 <= e->pos_x + 76 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80) {

                ship.Updatehp(renderer, gameTime);
                if (ship.life <= 0) {
                    isGameOver = true;
                }
            }
        }
        else if (e->height == 2) {
            if (shipx >= e->pos_x + 6 && shipx <= e->pos_x + 74 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80 ||
                shipx + 15 >= e->pos_x + 6 && shipx + 15 <= e->pos_x + 74 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80) {
                ship.Updatehp(renderer, gameTime);
                if (ship.life <= 0) {
                    isGameOver = true;
                }
            }
        }
        else if (e->height == 3) {
            if (shipx >= e->pos_x + 8 && shipx <= e->pos_x + 72 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80 ||
                shipx + 15 >= e->pos_x + 8 && shipx + 15 <= e->pos_x + 72 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80) {
                ship.Updatehp(renderer, gameTime);
                if (ship.life <= 0) {
                    isGameOver = true;
                }
            }
        }
        else if (e->height == 4) {
            if (shipx >= e->pos_x + 10 && shipx <= e->pos_x + 70 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80 ||
                shipx + 15 >= e->pos_x + 10 && shipx + 15 <= e->pos_x + 70 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80) {
                ship.Updatehp(renderer, gameTime);
                if (ship.life <= 0) {
                    isGameOver = true;
                }
            }
        }
        else if (e->height == 5) {
            if (shipx >= e->pos_x + 12 && shipx <= e->pos_x + 68 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80 ||
                shipx + 15 >= e->pos_x + 12 && shipx + 15 <= e->pos_x + 68 &&
                shipy >= e->pos_y && shipy <= e->pos_y + 80) {
                ship.Updatehp(renderer, gameTime);
                if (ship.life <= 0) {
                    isGameOver = true;
                }
            }
        }
    }
}

void Game::GameRenderer(SDL_Renderer* renderer, Ship& ship, std::vector<Shoot*>& shoots,
    Level level) {
    ship.Render(renderer);
    for (Shoot* s : shoots)
        s->Render(renderer);

    for (Ennemy* e : level.ennemies) {
        e->Render(renderer);
    }
}

void Game::Update(float dt, Ship& ship, std::vector<Shoot*>& shoots, Level* level, Up up,
    Right right, Left left, Down down, bool isUp, bool isRight, bool isLeft, bool isDown,
    float gameTime, float& shootCooldown, bool& canShoot) {
    if (gameTime - shootCooldown >= 0.25f) {
        canShoot = true;
    }
    if (canShoot) {
        shootCooldown = gameTime;
    }
    for (Ennemy* e : level->ennemies) {
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