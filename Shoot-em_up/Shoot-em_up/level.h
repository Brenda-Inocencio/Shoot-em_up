#pragma once
#include <string>
#include <vector>

struct SDL_Renderer;
struct string;
struct vector;
class Ennemy;

class Level {
public:
	std::vector<Ennemy*> ennemies;
	Ennemy* ennemy;
	~Level();
	void CreateEnnemy(std::string path, SDL_Renderer* renderer);
};
