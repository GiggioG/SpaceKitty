#include "Item.h"
#include "TextureManager.h"
#include "Presenter.h"
#include "ConfigManager.h"
#include "Engine.h"

extern ConfigManager* cfgm;

Item::Item() {};
Item::~Item() {};

void Item::init(ItemType _itemType, SDL_Rect spawnRect) {
	itemType = _itemType;
	if (itemType == ItemType::RACKET) {
		loc.rect.w = cfgm->cfg["RACKET_WIDTH"].i;
		loc.rect.h = cfgm->cfg["RACKET_HEIGHT"].i;
	} else {
		loc.rect.w = cfgm->cfg["PEPPER_WIDTH"].i;
		loc.rect.h = cfgm->cfg["PEPPER_HEIGHT"].i;
	}
	int2 centerPos = {
		rand() % spawnRect.w,
		rand() % spawnRect.h
	};
	loc.angle = randToOne() * 2 * M_PI;
	loc.rect.x = centerPos.x + spawnRect.x - loc.rect.w / 2;
	loc.rect.y = centerPos.y + spawnRect.y - loc.rect.h / 2;
	double speed = randToOne()*4 + 1;
	double direction = randToOne() * 2 * M_PI;
	velocity.x = speed * cos(direction);
	velocity.y = speed * sin(direction);

	angularVelocity = (randToOne()-0.5)/25;
};

void Item::update() {
	loc.rect.x += velocity.x;
	loc.rect.y += velocity.y;
	loc.angle += angularVelocity;
}

void Item::draw(int2 cameraPos) {
	Drawable d;
	d.texture = TextureManager::getItemTexture(itemType);
	d.rect = loc.rect.toSdlRect();
	d.angle = loc.angle;
	drawObject(d, cameraPos);
}

void Item::destruct() {

}

double2 Item::getWidthHeight(ItemType item){
	if (item == ItemType::NONE) { return { 0, 0 }; }
	double2 ret = { 0, 0 };
	if (item == ItemType::RACKET) {
		ret.x = cfgm->cfg["RACKET_WIDTH"].i;
		ret.y = cfgm->cfg["RACKET_HEIGHT"].i;
	}else {
		ret.x = cfgm->cfg["PEPPER_WIDTH"].i;
		ret.y = cfgm->cfg["PEPPER_HEIGHT"].i;
	}
	return ret;
}

bool Item::isPepper(ItemType item){
	return ((item == ItemType::PEPPER_GREEN) || (item == ItemType::PEPPER_YELLOW) || (item == ItemType::PEPPER_RED));
}
