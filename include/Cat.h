#pragma once
#include "defines.h"
#include "Item.h"
#include <queue>

struct BoostEffect {
	double timeExpires;
	double extraAcceleration;
	static struct Compare {
		bool operator()(const BoostEffect& a, const BoostEffect& b) {
			return a.timeExpires <= b.timeExpires;
		}
	};
};


class Cat {
public: 
	Cat();
	~Cat();

	void init();
	void update(int2 cameraPos);
	void draw(int2 cameraPos);
	void destruct();

	bool tryPickup(const Item& item);
	void breakRacket();
	RotatedRect loc;
	RotatedRect racketRange;
	ItemType* hittingWithRacketInHand = nullptr;

private:
	double2 velocity;
	double engineForce;
	double accelerationForce, boostAcceleration;
	double friction;

	ItemType leftHand =  ItemType::NONE;
	ItemType rightHand = ItemType::NONE;

	priority_queue<BoostEffect, vector<BoostEffect>, BoostEffect::Compare> boostEffects;

	void useBoost(double duration, double extraAcceleration);
	void useHand(ItemType* hand);
};

