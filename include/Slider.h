#pragma once

#include "defines.h"
#include <SDL.h>

class Slider {
public:
	Slider();
	~Slider();

	int max, min;
	int val;
	SDL_Rect rect;
	SDL_Rect thumbRect;

	void init(int2 coord, int width, int in_min, int in_max, int initialValue);
	void update();
	void draw();
	void destruct();
};