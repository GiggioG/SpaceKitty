#include "Button.h"
#include "defines.h"
#include "Presenter.h"
#include "World.h"
#include "Engine.h"

extern World world;
extern ConfigManager* cfgm;

Button::Button() {}
Button::~Button() {}

void Button::init(SDL_Texture* in_texture, SDL_Rect in_rect, bool* in_callback) {
	texture = in_texture;
	rect = in_rect;
	callback = in_callback;
}

void Button::update() {
	*callback = (world.m_inputManager.m_mouseOnClick && CoordInRect(world.m_inputManager.m_mouseCoor, rect));
}

void Button::draw() {
	Drawable d;
	d.texture = texture;
	d.rect = rect;
	if (CoordInRect(world.m_inputManager.m_mouseCoor, rect)) {
		int growHoriz = (int)((double)d.rect.w * (cfgm->cfg["BUTTON_GROW_FACTOR"].f - 1.0f));
		int growVert = (int)((double)d.rect.h * (cfgm->cfg["BUTTON_GROW_FACTOR"].f - 1.0f));

		d.rect.x -= growHoriz / 2;
		d.rect.w += growHoriz;

		d.rect.y -= growVert / 2;
		d.rect.h += growVert;
	}

	drawObject(d);
}

void Button::destruct() {

}
