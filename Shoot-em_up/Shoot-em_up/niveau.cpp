
#include "niveau.h"
#include <fstream>
#include <SDL3/SDL.h>
#include "ennemy.h"

Niveau::Niveau() {}

void Niveau::CreateEnnemy(std::string path, SDL_Renderer* renderer) {
	std::ifstream file(path);
	if (!file) {
		SDL_Log("Impossible d'ouvrir le fichier .txt");
	}
	else {
		std::string line;
		while (std::getline(file, line)) {
			int timer = 2;
			int nb = 1;
			int height = 1;
			float speed = 1;
			float hp = 1;
			if (line.empty()) {
				continue;
			}
			if (line == "time") {
				if (std::getline(file, line)) {
					timer = std::stoi(line);
				}
			}
			else if (line == "nb") {
				if (std::getline(file, line)) {
					nb = std::stoi(line);
				}
			}
			else if (line == "height") {
				if (std::getline(file, line)) {
					height = std::stoi(line);
				}
			}
			else if (line == "speed") {
				if (std::getline(file, line)) {
					speed = std::stof(line);
				}
			}
			else if (line == "hp") {
				if (std::getline(file, line)) {
					hp = std::stof(line);
				}
				ennemy = new Ennemy(timer, nb, height, speed, hp, renderer);
				ennemies.push_back(ennemy);
			}
		}
	}
}

Niveau::~Niveau() {
	delete ennemy; ennemy = nullptr;
}
