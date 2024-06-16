#pragma once

#include "defines.h"
#include "ConfigManager.h"
#include "Item.h"

extern ConfigManager* cfgm;

class TextureManager {
public:
	TextureManager();
	~TextureManager();

	static SDL_Texture* menu_background_texture;
	static SDL_Texture* game_background_texture;

	static SDL_Texture* play_button_texture;
	static SDL_Texture* quit_button_texture;

	static SDL_Texture* slider_body_texture;
	static SDL_Texture* slider_thumb_texture;

	static SDL_Texture* cat_texture;
	static SDL_Texture* pepper_green_texture;
	static SDL_Texture* pepper_yellow_texture;
	static SDL_Texture* pepper_red_texture;
	static SDL_Texture* racket_texture;
	static SDL_Texture* asteroid_texture;

	static SDL_Texture* playAgain_button_texture;

	static SDL_Texture* getItemTexture(ItemType item);

	void init();
	void destruct();
};