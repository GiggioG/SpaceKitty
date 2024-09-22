#include "defines.h"
#include "World.h"
#include "Gameplay.h"
#include "TextureManager.h"
#include "Presenter.h"
#include <algorithm>

extern World world;

Gameplay::Gameplay() {}
Gameplay::~Gameplay() {}

void Gameplay::init(){
	started = false;
	ended = false;
	cat.init();
	floatRadius = cfgm->cfg["FLOAT_RADIUS"].f;
	cameraSpeed = cfgm->cfg["CAMERA_SPEED"].f;
	movementBorderPadding = sqrt(cat.loc.rect.w * cat.loc.rect.w + cat.loc.rect.h * cat.loc.rect.h)/2; /// half of the cat's diagonal
	for(int i=0; i<5; i++){ /// TODO: seperate loops, spawn rates from config
		spawnItem();
		spawnAsteroid();
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
	/// calc cameraPos
	double2 cameraCenter = { cameraPos.x + Presenter::m_SCREEN_WIDTH / 2, cameraPos.y + Presenter::m_SCREEN_HEIGHT / 2 };
	double2 catCenter = { cat.loc.rect.x + cat.loc.rect.w / 2, cat.loc.rect.y + cat.loc.rect.h / 2 };
	double dst = distance(cameraCenter, catCenter);
	cameraPos.x += ceil((catCenter.x - cameraCenter.x) * cameraSpeed * (dst / (Presenter::m_SCREEN_WIDTH / 2 - movementBorderPadding)));
	cameraPos.y += ceil((catCenter.y - cameraCenter.y) * cameraSpeed * (dst / (Presenter::m_SCREEN_HEIGHT / 2 - movementBorderPadding)));
	if (catCenter.x < cameraPos.x + movementBorderPadding) {
		cameraPos.x -= (cameraPos.x + movementBorderPadding) - catCenter.x;
	}
	if (catCenter.x > cameraPos.x + Presenter::m_SCREEN_WIDTH - movementBorderPadding) {
		cameraPos.x += catCenter.x - (cameraPos.x + Presenter::m_SCREEN_WIDTH - movementBorderPadding);
	}
	if (catCenter.y < cameraPos.y + movementBorderPadding) {
		cameraPos.y -= (cameraPos.y + movementBorderPadding) - catCenter.y;
	}
	if (catCenter.y > cameraPos.y + Presenter::m_SCREEN_HEIGHT - movementBorderPadding) {
		cameraPos.y += catCenter.y - (cameraPos.y + Presenter::m_SCREEN_HEIGHT - movementBorderPadding);
	}

	/// old implementation
	//double2 target = {cat.loc.rect.x - Presenter::m_SCREEN_WIDTH/2, cat.loc.rect.y - Presenter::m_SCREEN_HEIGHT/2};
	//int dist = (int)distance({(double)cameraPos.x, (double)cameraPos.y}, target);
	//int speed = 10;
	//if(dist > speed * 3){
	//	cameraPos.x += ((int)target.x - cameraPos.x)*speed/dist; // lerp
	//	cameraPos.y += ((int)target.y - cameraPos.y)*speed/dist; // lerp
	//}
	
	/// update Items and Asteroids
	Rect allowedRect = getAllowedRect();
	/// todo: remove (and respawn) asteroids and items if too far away
	vector<list<Item>::iterator> itemsToBeErased;
	for (list<Item>::iterator it = items.begin(); it != items.end(); ++it) {
		it->update();
		double2 center = { it->loc.rect.x + it->loc.rect.w / 2, it->loc.rect.y + it->loc.rect.h / 2 };
		/// check bounds
		if (center.x < allowedRect.x) { it->loc.rect.x += allowedRect.w; }
		if (center.y < allowedRect.y) { it->loc.rect.y += allowedRect.h; }
		if (center.x > allowedRect.x + allowedRect.w) { it->loc.rect.x -= allowedRect.w; }
		if (center.y > allowedRect.y + allowedRect.h) { it->loc.rect.y -= allowedRect.h; }
		/// check collision with player
		if (collRotatedRectRotatedRect(it->loc, cat.loc)) {
			bool successPickup = cat.tryPickup(*it);
			if(successPickup){
				itemsToBeErased.push_back(it);
				spawnItem();
				continue;
			}
		}
	}
	for (list<Item>::iterator it : itemsToBeErased) {
		items.erase(it);
	}
	vector<list<Asteroid>::iterator> asteroidsToBeErased;
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
				asteroidsToBeErased.push_back(it);
				continue;
			}
		}
		/// check collision with player
		if (collRotatedRectRotatedRect(it->loc, cat.loc)) {
			// ended = true; /// TODO
		}
	}
	for (list<Asteroid>::iterator it : asteroidsToBeErased) {
		asteroids.erase(it);
	}
}

void Gameplay::draw() {
	Drawable d;
	d.texture = TextureManager::game_background_texture;
	int x = cameraPos.x / Presenter::m_SCREEN_WIDTH;
	int y = cameraPos.y / Presenter::m_SCREEN_HEIGHT;
	if (cameraPos.x < 0) { x--; }
	if (cameraPos.y < 0) { y--; }
	d.rect = { 0, 0, Presenter::m_SCREEN_WIDTH, Presenter::m_SCREEN_HEIGHT };
	for (int xoff = 0; xoff <= 1; xoff++) {
		for (int yoff = 0; yoff <= 1; yoff++) {
			d.rect.x = (x + xoff) * Presenter::m_SCREEN_WIDTH;
			d.rect.y = (y + yoff) * Presenter::m_SCREEN_HEIGHT;
			drawObject(d, cameraPos);
		}
	}

	/*int2 where = {-(cameraPos.x/Presenter::m_SCREEN_WIDTH)*Presenter::m_SCREEN_WIDTH + cameraPos.x, -(cameraPos.y/Presenter::m_SCREEN_HEIGHT)*Presenter::m_SCREEN_HEIGHT + cameraPos.y};
	drawObject(TextureManager::game_background_texture, where);
	drawObject(TextureManager::game_background_texture, int2(where.x - Presenter::m_SCREEN_WIDTH, where.y));
	drawObject(TextureManager::game_background_texture, int2(where.x, where.y - Presenter::m_SCREEN_HEIGHT));
	drawObject(TextureManager::game_background_texture, int2(where.x - Presenter::m_SCREEN_WIDTH, where.y - Presenter::m_SCREEN_HEIGHT));*/

	for (list<Asteroid>::iterator it = asteroids.begin(); it != asteroids.end(); ++it) {
		it->draw(cameraPos);
	}
	for (list<Item>::iterator it = items.begin(); it != items.end(); ++it) {
		it->draw(cameraPos);
	}

	string timeString = to_string(time);
	drawNum(timeString.substr(0, timeString.size()-3), {20, 20}, 50);

	cat.draw(cameraPos);
}


void Gameplay::destruct() {
	cat.destruct();
}

Rect Gameplay::getAllowedRect(){
	return {
		(double)(cameraPos.x - floatRadius), (double)(cameraPos.y - floatRadius),
		Presenter::m_SCREEN_WIDTH + 2*floatRadius, Presenter::m_SCREEN_HEIGHT + 2*floatRadius
	};
}

void Gameplay::spawnItem(){
	Item i;
	ItemType itemType = (ItemType)((rand() % 4) + 1);
	i.init(itemType, getAllowedRect().toSdlRect());
	//std::cout << i.loc.rect.x << ' ' << i.loc.rect.y << '\n';
	items.push_back(i);
}

void Gameplay::spawnAsteroid(){
	Asteroid a;
	a.init(getAllowedRect().toSdlRect());
	asteroids.push_back(a);
}
