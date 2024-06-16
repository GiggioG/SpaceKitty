#include "defines.h"
#include "World.h"
#include "Gameplay.h"
#include "TextureManager.h"
#include "Presenter.h"

extern World world;

Gameplay::Gameplay() {}
Gameplay::~Gameplay() {}

void Gameplay::init(){
	started = false;
	ended = false;
	cat.init();
	/// TODO: spawn items and asteroids
	for(int i=0; i<100; i++){
		spawnItem();
	}
}

void Gameplay::update() {
	if (!started) { /// TODO
		started = true;
		timeStarted = SDL_GetTicks();
	}

	if (!ended) {
		uint32_t currentTime = SDL_GetTicks();
		time = (currentTime - timeStarted) / (double)1000;
	}
	cat.update(cameraPos);
	double2 target = {cat.loc.rect.x - Presenter::m_SCREEN_WIDTH/2, cat.loc.rect.y - Presenter::m_SCREEN_HEIGHT/2};
	int dist = (int)distance({(double)cameraPos.x, (double)cameraPos.y}, target);
	int speed = 20;
	if(dist > speed){
		cameraPos.x += ((int)target.x - cameraPos.x)*speed/dist; // learp
		cameraPos.y += ((int)target.y - cameraPos.y)*speed/dist; // learp
	}
	// cameraPos = int2(cat.loc.rect.x, cat.loc.rect.y);
	Rect allowedRect = getAllowedRect();
	/// todo: remove (and respawn) asteroids and items if too far away
	for (list<Item>::iterator it = (--items.end()); it != items.begin(); --it) {
		it->update();
		/// check bounds
		if ((it->loc.rect.x + it->loc.rect.w / 2) < allowedRect.x) { it->loc.rect.x += allowedRect.w; }
		if ((it->loc.rect.y + it->loc.rect.h / 2) < allowedRect.y) { it->loc.rect.y += allowedRect.h; }
		if ((it->loc.rect.x + it->loc.rect.w / 2) > allowedRect.x + allowedRect.w) { it->loc.rect.x -= allowedRect.w; }
		if ((it->loc.rect.y + it->loc.rect.h / 2) > allowedRect.y + allowedRect.h) { it->loc.rect.y -= allowedRect.h; }
		/// check collision with player
		if (collRotatedRectRotatedRect(it->loc, cat.loc)) {
			bool successPickup = cat.tryPickup(*it);
			if(successPickup){ 
				spawnItem();
				continue;
			}
		}
	}
	for (list<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ++it) {
		it->update();
		/// check bounds
		if ((it->loc.rect.x + it->loc.rect.w / 2) < allowedRect.x) { it->loc.rect.x += allowedRect.w; }
		if ((it->loc.rect.y + it->loc.rect.h / 2) < allowedRect.y) { it->loc.rect.y += allowedRect.h; }
		if ((it->loc.rect.x + it->loc.rect.w / 2) > allowedRect.x + allowedRect.w) { it->loc.rect.x -= allowedRect.w; }
		if ((it->loc.rect.y + it->loc.rect.h / 2) > allowedRect.y + allowedRect.h) { it->loc.rect.y -= allowedRect.h; }
		/// check if hit
		if (cat.hittingWithRacketInHand != nullptr) {
			if (collRotatedRectRotatedRect(cat.racketRange, it->loc)) {
				cat.breakRacket();
				asteroids.erase(it);
				continue;
			}
		}
		/// check collision with player
		if (collRotatedRectRotatedRect(it->loc, cat.loc)) {
			ended = true;
		}
	}

}

void Gameplay::draw() {
	int2 where = {-(cameraPos.x/Presenter::m_SCREEN_WIDTH)*Presenter::m_SCREEN_WIDTH + cameraPos.x, -(cameraPos.y/Presenter::m_SCREEN_HEIGHT)*Presenter::m_SCREEN_HEIGHT + cameraPos.y};
	drawObject(TextureManager::game_background_texture, where);
	drawObject(TextureManager::game_background_texture, int2(where.x - Presenter::m_SCREEN_WIDTH, where.y));
	drawObject(TextureManager::game_background_texture, int2(where.x, where.y - Presenter::m_SCREEN_HEIGHT));
	drawObject(TextureManager::game_background_texture, int2(where.x - Presenter::m_SCREEN_WIDTH, where.y - Presenter::m_SCREEN_HEIGHT));

	string timeString = to_string(time);
	drawNum(timeString.substr(0, timeString.size()-3), {20, 20}, 50);

	cat.draw(cameraPos);
}


void Gameplay::destruct() {
	cat.destruct();
}

Rect Gameplay::getAllowedRect(){
	return 	cat.loc.rect;
	return {
		(double)(cameraPos.x - 1000), (double)(cameraPos.y - 1000),
		(double)(cameraPos.x + Presenter::m_SCREEN_WIDTH + 1000), (double)(cameraPos.y + Presenter::m_SCREEN_HEIGHT + 1000)
	};
}

void Gameplay::spawnItem(){
	Item i;
	ItemType itemType = (ItemType)((rand() % 4) + 1);
	i.init(itemType, getAllowedRect().toSdlRect());
	items.push_back(i);
}

void Gameplay::spawnAsteroid(){
	Asteroid a;
	a.init(getAllowedRect().toSdlRect());
	asteroids.push_back(a);
}
