#pragma once
#include <string>
#include <vector>

struct SDL_Renderer;
class Ennemy;

class Niveau {
public:
	std::vector<Ennemy*> ennemies;
	Ennemy* ennemy;
	Niveau();
	~Niveau();
	void CreateEnnemy(std::string path, SDL_Renderer* renderer);
};
