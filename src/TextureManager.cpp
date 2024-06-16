#include "TextureManager.h"
#include "Presenter.h"


SDL_Texture* TextureManager::menu_background_texture = nullptr;
SDL_Texture* TextureManager::game_background_texture = nullptr;

SDL_Texture* TextureManager::play_button_texture = nullptr;
SDL_Texture* TextureManager::quit_button_texture = nullptr;

SDL_Texture* TextureManager::slider_body_texture = nullptr;
SDL_Texture* TextureManager::slider_thumb_texture = nullptr;

SDL_Texture* TextureManager::cat_texture = nullptr;
SDL_Texture* TextureManager::pepper_green_texture = nullptr;
SDL_Texture* TextureManager::pepper_yellow_texture = nullptr;
SDL_Texture* TextureManager::pepper_red_texture = nullptr;
SDL_Texture* TextureManager::racket_texture = nullptr;
SDL_Texture* TextureManager::asteroid_texture = nullptr;

SDL_Texture* TextureManager::playAgain_button_texture = nullptr;

TextureManager::TextureManager() {}
TextureManager::~TextureManager() {}

SDL_Texture* TextureManager::getItemTexture(ItemType item){
	switch (item) {
	case ItemType::PEPPER_GREEN :
		return pepper_green_texture;
	case ItemType::PEPPER_YELLOW:
		return pepper_yellow_texture;
	case ItemType::PEPPER_RED:
		return pepper_red_texture;
	case ItemType::RACKET:
		return racket_texture;
	}
	return nullptr;
}

void TextureManager::init() {
	menu_background_texture = loadTexture(cfgm->cfg["MENU_BACKGROUND_BMP"].s);
	game_background_texture = loadTexture(cfgm->cfg["GAME_BACKGROUND_BMP"].s);

	play_button_texture = loadTexture(cfgm->cfg["PLAY_BUTTON_BMP"].s);
	quit_button_texture = loadTexture(cfgm->cfg["QUIT_BUTTON_BMP"].s);

	slider_body_texture = loadTexture(cfgm->cfg["SLIDER_BODY_BMP"].s);
	slider_thumb_texture = loadTexture(cfgm->cfg["SLIDER_THUMB_BMP"].s);

	cat_texture = loadTexture(cfgm->cfg["CAT_TEXTURE"].s);
	pepper_green_texture = loadTexture(cfgm->cfg["PEPPER_GREEN_TEXTURE"].s);
	pepper_yellow_texture = loadTexture(cfgm->cfg["PEPPER_YELLOW_TEXTURE"].s);
	pepper_red_texture = loadTexture(cfgm->cfg["PEPPER_RED_TEXTURE"].s);
	racket_texture = loadTexture(cfgm->cfg["RACKET_TEXTURE"].s);
	asteroid_texture = loadTexture(cfgm->cfg["ASTEROID_TEXTURE"].s);

	playAgain_button_texture = loadTexture(cfgm->cfg["PLAYAGAIN_BUTTON_TEXTURE"].s);
}

void TextureManager::destruct() {
	SDL_DestroyTexture(menu_background_texture);
	SDL_DestroyTexture(game_background_texture);

	SDL_DestroyTexture(play_button_texture);
	SDL_DestroyTexture(quit_button_texture);

	SDL_DestroyTexture(slider_body_texture);
	SDL_DestroyTexture(slider_thumb_texture);

	SDL_DestroyTexture(cat_texture);
	SDL_DestroyTexture(pepper_green_texture);
	SDL_DestroyTexture(pepper_green_texture);
	SDL_DestroyTexture(pepper_green_texture);
	SDL_DestroyTexture(racket_texture);
	SDL_DestroyTexture(asteroid_texture);

	SDL_DestroyTexture(playAgain_button_texture);
}