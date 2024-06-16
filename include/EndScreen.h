#pragma once

#include "Button.h"
#include "defines.h"

class EndScreen {
public:
	EndScreen();
	~EndScreen();

	Button playAgainButton, quitButton;
	bool playAgainClicked = false, quitClicked = false;

	void init();
	void update();
	void draw();
	void destruct();
};