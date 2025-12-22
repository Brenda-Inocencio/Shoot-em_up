#pragma once
#include <vector>

struct SDL_Renderer;
class Shoot;
class Ennemy;
class Level;
class Ship;
class Score;
class Up;
class Down;
class Left;
class Right;

class Game {
public:
	void Collisions(SDL_Renderer* renderer, std::vector<Shoot*>& shoots,
		std::vector<Ennemy*>& ennemies, Ship& ship, float now, Score* score, bool& isGameOver,
		bool& isWin);
	void GameRenderer(SDL_Renderer* renderer, Ship& ship, std::vector<Shoot*>& shoots,
		Level level);
	void Update(float dt, Ship& ship, std::vector<Shoot*>& shoots, Level* level, Up up,
		Right right, Left left, Down down, bool isUp, bool isRight, bool isLeft, bool isDown,
		float gameTime, float& shootCooldown, bool& canShoot);
};