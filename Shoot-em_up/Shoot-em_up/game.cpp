#include "game.h"
#include <vector>
#include "score.h"
#include "ship.h"
#include "shoot.h"
#include "move.h"
#include "niveau.h"
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
            ship.Updatehp(renderer, gameTime);
            if (ship.life <= 0) {
                isGameOver = true;
            }
        }
    }
}

void Game::GameRenderer(SDL_Renderer* renderer, Ship& ship, std::vector<Shoot*>& shoots,
    Niveau* niveau) {
    ship.Render(renderer);
    for (Shoot* s : shoots)
        s->Render(renderer);

    for (Ennemy* e : niveau->ennemies) {
        e->Render(renderer);
    }
}

void Game::Update(float dt, Ship& ship, std::vector<Shoot*>& shoots, Niveau* niveau, Up& up,
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