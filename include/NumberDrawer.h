#pragma	once

#include <SDL.h>
#include "defines.h"

class NumberDrawer {
public:
	NumberDrawer();
	~NumberDrawer();

	void init();
	void drawNum(std::string num, int2 pos, int height);
	void destruct();

private:
	SDL_Texture* numerals[10];
	SDL_Texture* decimalPoint;
	int2 numeralDims[10];
	int2 decimalPointDims;
};


void drawNum(std::string num, int2 pos, int height);
