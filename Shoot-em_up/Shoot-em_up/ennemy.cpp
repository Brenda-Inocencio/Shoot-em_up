#include "ennemy.h"
#include <fstream>
#include <string>
#include <SDL3/SDL.h>

Ennemy::Ennemy() {
	time = 0;
	nb = 0;
	height = 0;
	speed = 0;
	hp = 0;
}

Ennemy::Ennemy(int _time, int _nb, int _height, float _speed, float _hp) {
	time = _time;
	nb = _nb;
	height = _height;
	speed = _speed;
	hp = _hp;
}