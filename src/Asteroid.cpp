#include "Asteroid.h"
#include "TextureManager.h"
#include "Presenter.h"
#include "ConfigManager.h"
#include "Engine.h"

extern ConfigManager* cfgm;

Asteroid::Asteroid() {};
Asteroid::~Asteroid() {};

void Asteroid::init(SDL_Rect spawnRect) {
	int2 centerPos = {
		rand() % spawnRect.w,
		rand() % spawnRect.h
	};
	loc.rect.x = centerPos.x + spawnRect.x - loc.rect.w / 2;
	loc.rect.y = centerPos.y + spawnRect.y - loc.rect.h / 2;

	double speed = randToOne()*4 + 1;
	double direction = randToOne() * 2 * M_PI;
	velocity.x = speed * cos(direction);
	velocity.y = speed * sin(direction);

	angularVelocity = (randToOne()-0.5)/25;
};

void Asteroid::update() {
	loc.rect.x += velocity.x;
	loc.rect.y += velocity.y;
	loc.angle += angularVelocity;
}

void Asteroid::draw(int2 cameraPos) {
	Drawable d;
	d.texture = TextureManager::asteroid_texture;
	d.rect = loc.rect.toSdlRect();
	d.angle = loc.angle;
	drawObject(d, cameraPos);
}

void Asteroid::destruct() {

}
