#include "MenuScreen.h"
#include "Presenter.h"
#include "TextureManager.h"
#include "World.h"
#include "Button.h"

extern World world;

MenuScreen::MenuScreen() {}

MenuScreen::~MenuScreen() {}

void MenuScreen::init() {
	playButton.init(TextureManager::play_button_texture, { 532, 900, 256, 128 }, &playClicked);
	quitButton.init(TextureManager::quit_button_texture, { 1132, 900, 256, 128 }, &quitClicked);
}

void MenuScreen::update() {
	playButton.update();
	quitButton.update();
}

void MenuScreen::draw() {
	drawObject(TextureManager::menu_background_texture);

	playButton.draw();
	quitButton.draw();
}

void MenuScreen::destruct() {
	playButton.destruct();
	quitButton.destruct();
}
