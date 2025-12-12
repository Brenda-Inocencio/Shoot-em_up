#pragma once

class Ship;
class Shoot;

class Up {
public:
	void Moving(Ship& ship, float dt);
	void Moving(Shoot& shoot, float dt);
};

class Right {
public:
	void Moving(Ship& ship, float dt);
};

class Left {
public:
	void Moving(Ship& ship, float dt);
};

class Down {
public:
	void Moving(Ship& ship, float dt);
};