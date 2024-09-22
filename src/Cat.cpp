#include "Cat.h"
#include "Presenter.h"
#include "ConfigManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "World.h"
#include <cmath>

extern ConfigManager* cfgm;
extern World world;

Cat::Cat() {}
Cat::~Cat() {}

void Cat::init() {
	rightHand = ItemType::PEPPER_GREEN;
	leftHand = ItemType::PEPPER_GREEN;

	loc.rect.w = cfgm->cfg["CAT_WIDTH"].i;
	loc.rect.h = cfgm->cfg["CAT_HEIGHT"].i;
	loc.rect.x = Presenter::m_SCREEN_WIDTH / 2 - loc.rect.w / 2;
	loc.rect.y = Presenter::m_SCREEN_HEIGHT / 2 - loc.rect.h / 2;
	loc.angle = 0;

	engineForce = cfgm->cfg["ENGINE_FORCE"].f;
	friction = cfgm->cfg["FRICTION_COEFFICIENT"].f;

	racketRectWidth = cfgm->cfg["RACKET_RECT_WIDTH"].f;
	racketRectHeight = cfgm->cfg["RACKET_RECT_HEIGHT"].f;
}

void Cat::update(int2 cameraPos) {
	/// remove expired effects
	while (!boostEffects.empty() && boostEffects.top().timeExpires <= SDL_GetTicks()) {
		boostAcceleration -= boostEffects.top().extraAcceleration;
		boostEffects.pop();
	}
	/// cat using items
	hittingWithRacketInHand = nullptr;
	if (world.m_inputManager.m_mouseIsPressed) {
		useHand(&leftHand);
	}
	if (world.m_inputManager.m_mouseIsRightPressed) {
		useHand(&rightHand);
	}
	/// calc rect for racket collision with asteroids
	double2 catCenter = { loc.rect.x + loc.rect.w / 2, loc.rect.y + loc.rect.h / 2 };
	racketRange.rect.w = racketRectWidth;
	racketRange.rect.h = racketRectHeight;
	double2 center = rotatePointAroundCenter({ loc.rect.x + loc.rect.w + racketRange.rect.w/2, loc.rect.y + loc.rect.h / 2 }, catCenter, loc.angle);
	racketRange.rect.x = center.x - racketRange.rect.w / 2;
	racketRange.rect.y = center.y - racketRange.rect.h / 2;
	racketRange.angle = loc.angle;
	Drawable kupata;
	kupata.texture = TextureManager::menu_background_texture;
	kupata.rect = racketRange.rect.toSdlRect();
	kupata.angle = loc.angle;
	drawObject(kupata, cameraPos);
	/// cat physics
	double2 catPoint = {
		(double)(loc.rect.x + loc.rect.w / 2),
		(double)(loc.rect.y + loc.rect.h / 2)
	};
	double2 mousePoint = {
		(double)(world.m_inputManager.m_mouseCoor.x + cameraPos.x),
		(double)(world.m_inputManager.m_mouseCoor.y + cameraPos.y)
	};

	accelerationForce = world.m_inputManager.keyIsPressed(SDL_SCANCODE_SPACE) * engineForce;
	accelerationForce += boostAcceleration;

	loc.angle = angle2Points(catPoint, mousePoint);
	velocity.x += accelerationForce * cos(loc.angle);
	velocity.y += accelerationForce * sin(loc.angle);

	loc.rect.x += velocity.x;
	loc.rect.y += velocity.y;

	velocity.y *= friction;
	velocity.x *= friction;
}

void Cat::draw(int2 cameraPos) {
	Drawable d;
	d.texture = TextureManager::cat_texture;
	d.rect = loc.rect.toSdlRect();
	d.angle = loc.angle;
	drawObject(d, cameraPos);
	double2 catCenter = {loc.rect.x + loc.rect.w/2, loc.rect.y + loc.rect.h/2};
	if (leftHand != ItemType::NONE) {
		Drawable leftItem;
		leftItem.angle = loc.angle;
		leftItem.texture = TextureManager::getItemTexture(leftHand);
		double2 drawableDims = Item::getWidthHeight(leftHand);
		leftItem.rect.w = drawableDims.x;
		leftItem.rect.h = drawableDims.y;
		double2 center = rotatePointAroundCenter({ loc.rect.x + loc.rect.w, loc.rect.y }, catCenter, loc.angle);
		leftItem.rect.x = (int)center.x - drawableDims.x/2;
		leftItem.rect.y = (int)center.y - drawableDims.y/2;
		drawObject(leftItem, cameraPos);
	}
	if (rightHand != ItemType::NONE) {
		Drawable rightItem;
		rightItem.angle = loc.angle;
		rightItem.texture = TextureManager::getItemTexture(rightHand);
		double2 drawableDims = Item::getWidthHeight(rightHand);
		rightItem.rect.w = drawableDims.x;
		rightItem.rect.h = drawableDims.y;
		double2 center = rotatePointAroundCenter({ loc.rect.x + loc.rect.w, loc.rect.y + loc.rect.h}, catCenter, loc.angle);
		rightItem.rect.x = (int)center.x - drawableDims.x / 2;
		rightItem.rect.y = (int)center.y - drawableDims.y / 2;
		drawObject(rightItem, cameraPos);
	}
}

void Cat::destruct() {
}

bool Cat::tryPickup(const Item& item){
	if (leftHand == ItemType::NONE) {
		leftHand = item.itemType;
		return true;
	} else if(rightHand == ItemType::NONE) {
		rightHand = item.itemType;
		return true;
	}
	return false;
}

void Cat::breakRacket() {
	if (*hittingWithRacketInHand == ItemType::RACKET) {
		*hittingWithRacketInHand = ItemType::NONE;
		hittingWithRacketInHand = nullptr;
	}
}

void Cat::useBoost(double duration, double extraAcceleration){
	BoostEffect eff;
	eff.timeExpires = SDL_GetTicks() + duration;
	eff.extraAcceleration = extraAcceleration;
	boostEffects.push(eff);
	boostAcceleration += extraAcceleration;
}

void Cat::useHand(ItemType* hand) {
	if (*hand == ItemType::NONE) { return; }
	if (Item::isPepper(*hand)) {
		if (*hand == ItemType::PEPPER_GREEN) {
			useBoost(cfgm->cfg["PEPPER_GREEN_DURATION"].i, cfgm->cfg["PEPPER_GREEN_BOOST"].f);
		} else if (*hand == ItemType::PEPPER_YELLOW) {
			useBoost(cfgm->cfg["PEPPER_YELLOW_DURATION"].i, cfgm->cfg["PEPPER_YELLOW_BOOST"].f);
		} else if (*hand == ItemType::PEPPER_RED) {
			useBoost(cfgm->cfg["PEPPER_RED_DURATION"].i, cfgm->cfg["PEPPER_RED_BOOST"].f);
		}
		*hand = ItemType::NONE;
	} else {
		hittingWithRacketInHand = hand;
	}
}