#pragma once
#include "defines.h"

class Asteroid
{
public:
	Asteroid();
	~Asteroid();

	void init(SDL_Rect spawnRect);
	void update();
	void draw(int2 cameraPos);
	void destruct();

	RotatedRect loc;
	double2 velocity;
	double angularVelocity;
};
