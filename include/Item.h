#pragma once
#include "defines.h"

enum class ItemType {
	NONE = 0,
	PEPPER_GREEN = 1,
	PEPPER_YELLOW = 2,
	PEPPER_RED = 3,
	RACKET = 4
};

class Item
{
public:
	Item();
	~Item();

	void init(ItemType _itemType, SDL_Rect spawnRect);
	void update();
	void draw(int2 cameraPos);
	void destruct();

	RotatedRect loc;
	ItemType itemType;
	double2 velocity;
	double angularVelocity;

	static double2 getWidthHeight(ItemType item);
	static bool isPepper(ItemType item);
};
