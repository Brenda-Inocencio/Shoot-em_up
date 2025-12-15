#include "move.h"
#include "ship.h"
#include "shoot.h"

void Up::Moving(Ship& ship, float dt) {
	if (ship.pos_y > 0) {
		ship.pos_y -= 150.0 * dt;
	}
}

void Up::Moving(Shoot* shoot, float dt) {
	shoot->pos_y -= 80 * dt;
}

void Right::Moving(Ship& ship, float dt) {
	if (ship.pos_x < 944) {
		ship.pos_x += 150.0 * dt;
	}
}

void Left::Moving(Ship& ship, float dt) {
	if (ship.pos_x > 0) {
		ship.pos_x -= 150.0 * dt;
	}
}

void Down::Moving(Ship& ship, float dt) {
	if (ship.pos_y < 688) {
		ship.pos_y += 150.0 * dt;
	}
}