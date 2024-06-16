#include "NumberDrawer.h"
#include "Presenter.h"
#include "World.h"
#include <string>

extern World world;

NumberDrawer::NumberDrawer() {}
NumberDrawer::~NumberDrawer() {}

void NumberDrawer::init() {
	for (int i = 0; i <= 9; i++) {
		std::string path = "numerals/n#.bmp";
		path[10] = i + '0';
		numerals[i] = loadTexture(path);
		SDL_QueryTexture(numerals[i], NULL, NULL, &numeralDims[i].x, &numeralDims[i].y);
	}
	decimalPoint = loadTexture("numerals/decimalPoint.bmp");
	SDL_QueryTexture(decimalPoint, NULL, NULL, &decimalPointDims.x, &decimalPointDims.y);
}

void NumberDrawer::drawNum(std::string num, int2 pos, int height) {
	Drawable dr;
	dr.angle = 0;
	int currX = pos.x;
	for (int i = 0; i < num.size(); i++) {
		if (num[i] == '.') {
			double mul = (double)height / (double)decimalPointDims.y;
			dr.texture = decimalPoint;
			dr.rect.x = currX;
			dr.rect.y = pos.y;
			dr.rect.w = (int)(decimalPointDims.x * mul);
			dr.rect.h = (int)(decimalPointDims.y * mul);
			drawObject(dr, {0, 0});
			currX += dr.rect.w;
			continue;
		}

		int d = num[i] - '0';

		double mul = (double)height / (double) numeralDims[d].y;

		dr.texture = numerals[d];
		dr.rect.x = currX;
		dr.rect.y = pos.y;
		dr.rect.w = (int)(numeralDims[d].x * mul);
		dr.rect.h = (int)(numeralDims[d].y * mul);
		drawObject(dr);
		currX += dr.rect.w;
	}
}

void NumberDrawer::destruct() {
	for (int i = 0; i <= 9; i++) {
		SDL_DestroyTexture(numerals[i]);
	}
}


void drawNum(std::string num, int2 pos, int height) {
	world.m_numberDrawer.drawNum(num, pos, height);
}
