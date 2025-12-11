#pragma once

class Ship;
class Shoot;

class Up {
public:
	void Moving(Ship& ship);
	void Moving(Shoot& shoot);
};

class Right {
public:
	void Moving(Ship& ship);
};

class Left {
public:
	void Moving(Ship& ship);
};

class Down {
public:
	void Moving(Ship& ship);
};