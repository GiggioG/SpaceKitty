#include "Presenter.h"
#include "TextureManager.h"
#include "Slider.h"
#include "Engine.h"
#include "World.h"

extern World world;

Slider::Slider() {}
Slider::~Slider() {}

void Slider::init(int2 coord, int width, int in_min, int in_max, int initialValue){
	rect.x = coord.x;
	rect.y = coord.y;
	rect.w = width;
	rect.h = 30;
	min = in_min;
	max = in_max;
	val = initialValue;
}

void Slider::update() {
	thumbRect.w = 15;
	thumbRect.h = 40;
	thumbRect.x = rangeMap(min, max, rect.x + thumbRect.w / 2, rect.x + rect.w - thumbRect.w - thumbRect.w/2, val);
	thumbRect.y = rect.y - (thumbRect.h - rect.h) / 2;

	if (world.m_inputManager.m_mouseIsHolded && CoordInRect(world.m_inputManager.m_mouseCoor, rect)) {
		val = rangeMap(rect.x + thumbRect.w, rect.x + rect.w - thumbRect.w, min, max, world.m_inputManager.m_mouseCoor.x);
		if (val < min) { val = min; }
		else if (val > max) { val = max; }
	}
}

void Slider::draw() {
	Drawable sliderBody;
	sliderBody.rect = rect;
	sliderBody.texture = TextureManager::slider_body_texture;
	drawObject(sliderBody);

	Drawable sliderThumb;
	sliderThumb.rect = thumbRect;
	sliderThumb.texture = TextureManager::slider_thumb_texture;
	drawObject(sliderThumb);

	drawNum(to_string(val), { rect.x + rect.w + 20, rect.y-1 }, 32);
}

void Slider::destruct() {

}