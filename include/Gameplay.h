#pragma once

#include "defines.h"
#include "Cat.h"
#include "Item.h"
#include "Asteroid.h"
#include <list>

class Gameplay {
public:
	Gameplay();
	~Gameplay();

	bool started = false, ended = false;

	void init();
	void update();
	void draw();
	void destruct();
private:
	int2 cameraPos = { 0, 0 };
	uint32_t timeStarted;
	double time = 0;
	Cat cat;
	list<Item> items;
	list<Asteroid> asteroids;
	double floatRadius;
	double movementBorderPadding;
	double cameraSpeed;

	Rect getAllowedRect();
	void spawnItem();
	void spawnAsteroid();
};