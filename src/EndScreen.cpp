#include "EndScreen.h"
#include "Presenter.h"
#include "TextureManager.h"
#include "World.h"
#include "Button.h"

extern World world;

EndScreen::EndScreen() {}
EndScreen::~EndScreen() {}

void EndScreen::init() {
	playAgainButton.init(TextureManager::playAgain_button_texture, { 532, 900, 256, 128 }, &playAgainClicked);
	quitButton.init(TextureManager::quit_button_texture, { 1132, 900, 256, 128 }, &quitClicked);
}

void EndScreen::update() {
	playAgainButton.update();
	quitButton.update();
}

void EndScreen::draw() {
	drawObject(TextureManager::menu_background_texture);

	//Drawable scoresBkg;
	//scoresBkg.rect = {660, 200, 600, 600};
	//scoresBkg.texture = TextureManager::scoresbackground_texture;
	//drawObject(scoresBkg);

	//drawNum(to_string(score), { 900, 350 }, 150);
	//drawNum(to_string(bonboni), { 920, 610 }, 100);

	playAgainButton.draw();
	quitButton.draw();
}

void EndScreen::destruct() {
	playAgainButton.destruct();
	quitButton.destruct();
}
