#pragma once

#include "Presenter.h"
#include "InputManager.h"
#include "ConfigManager.h"
#include "TextureManager.h"
#include "NumberDrawer.h"

#include "MenuScreen.h"
#include "Gameplay.h"
#include "EndScreen.h"

class World {
public:
	World();
	~World();

	GameState m_gameState = GameState::NONE;

	ConfigManager m_configManager;
	Presenter m_presenter;
	InputManager m_inputManager;
	TextureManager m_textureManager;
	NumberDrawer m_numberDrawer;

	MenuScreen m_menuScreen;
	Gameplay m_gameplay;
	EndScreen m_winScreen;

	void init();
	void run();
	void destroy();

	bool isRunning();

	void startGame();

	void playAgain();
	void quit();
private:
	bool m_isRunning;
};