#pragma once

#include "Button.h"
#include "Slider.h"
#include "defines.h"

class MenuScreen {
public:
	MenuScreen();
	~MenuScreen();

	Button playButton, quitButton;
	bool playClicked = false, quitClicked = false;

	void init();
	void update();
	void draw();
	void destruct();
};