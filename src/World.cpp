#include "World.h"
#include "defines.h"

extern World world;
extern ConfigManager* cfgm;

World::World(){ m_isRunning = true; }

World::~World() {}

void World::init(){
	m_gameState = GameState::MENU;
	m_configManager.init();
	cfgm = &m_configManager;
	m_presenter.init();
	m_textureManager.init();
	m_numberDrawer.init();

	m_menuScreen.init();
}

void World::run(){
	m_inputManager.handleInput();
	m_presenter.update();

	if (m_gameState == GameState::MENU) {
		startGame();
		return;
		m_menuScreen.update();
		m_menuScreen.draw();
		if (m_menuScreen.playClicked) {
			startGame();
		} else if (m_menuScreen.quitClicked) {
			quit();
		}
	} else if (m_gameState == GameState::PLAYING) {
		m_gameplay.update();
		m_gameplay.draw();

		if (m_gameplay.ended) {
			m_winScreen.init();
			m_gameState = GameState::ENDSCREEN;
		}
	} else if (m_gameState == GameState::ENDSCREEN) {
		m_winScreen.update();
		m_winScreen.draw();
		if (m_winScreen.playAgainClicked) {
			startGame();
		} else if (m_winScreen.quitClicked) {
			quit();
		}
	}

	m_presenter.draw();
}

// call destroy for all classes to prevent memory leak
void World::destroy(){
	m_textureManager.destruct();
	m_numberDrawer.destruct();
	m_configManager.destruct();

	m_gameplay.destruct();
	m_winScreen.destruct();

	SDL_DestroyRenderer(m_presenter.m_main_renderer);
	SDL_DestroyWindow(m_presenter.m_main_window);
}

bool World::isRunning(){
	return m_isRunning;
}

void World::startGame() {
	m_gameState = GameState::PLAYING;
	m_gameplay.init();
}

void World::quit() {
	m_isRunning = false;
	std::cout << "Game quit!\n";
	exit(0);
}