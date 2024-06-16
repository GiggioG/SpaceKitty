#pragma once
#include <SDL.h>

class Button {
public:
	Button();
	~Button();

	SDL_Texture* texture = nullptr;
	SDL_Rect rect = {-1, -1, -1, -1};
	bool* callback;
	
	void init(SDL_Texture* in_texture, SDL_Rect in_rect, bool* in_callback);
	void update();
	void draw();
	void destruct();
};