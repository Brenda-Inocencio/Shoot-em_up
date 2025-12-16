
#include "niveau.h"
#include <fstream>
#include <SDL3/SDL.h>
#include "ennemy.h"

void Niveau::CreateEnnemy(std::string path, SDL_Renderer* renderer) {
	std::ifstream file(path);
	if (!file) {
		SDL_Log("Impossible d'ouvrir le fichier .txt");
	}
	else {
		std::string line;
		float timer = 2.0f;
		int nb = 1;
		int height = 1;
		float speed = 1;
		float hp = 1;
		while (std::getline(file, line)) {
			if (line.empty()) {
				continue;
			}
			if (line == "time") {
				if (std::getline(file, line)) {
					timer = std::stof(line);
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
			}
			else if (line == "nb") {
				if (std::getline(file, line)) {
					nb = std::stoi(line);
				}
				for (int i = 0; i < nb; i++) {
					ennemy = new Ennemy(timer, height, speed, hp, renderer);
					ennemies.push_back(ennemy);
					
				}
			}
		}
	}
}

Niveau::~Niveau() {
	ennemies.clear();
}
