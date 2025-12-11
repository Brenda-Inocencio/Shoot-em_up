#include "move.h"
#include "ship.h"
#include "shoot.h"

void Up::Moving(Ship& ship) {
	ship.pos_y -= 10;
}

void Up::Moving(Shoot& shoot) {
	shoot.pos_y -= 10;
}

void Right::Moving(Ship& ship) {
	ship.pos_x += 10;
}

void Left::Moving(Ship& ship) {
	ship.pos_x -= 10;
}

void Down::Moving(Ship& ship) {
	ship.pos_y += 10;
}