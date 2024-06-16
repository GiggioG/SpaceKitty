#pragma once 

#include <iomanip>

#include "Engine.h"

using namespace std;

class Presenter
{
public:
	static SDL_Window* m_main_window;
	static SDL_Renderer* m_main_renderer;

	static int m_SCREEN_WIDTH;
	static int m_SCREEN_HEIGHT;

	void init();
	void update();
	void draw();

	SDL_Renderer* getRenderer();

	static void drawObject(SDL_Texture* texture, int2 cameraPos);
	static void drawObject(Drawable& drawable, int2 cameraPos);


private:
	int2 screenCenter;

	void improveRenderer();
};

namespace
{
	template <typename T>
	void drawObject(T& t, int2 cameraPos = {0, 0}) {
		Presenter::drawObject(t, cameraPos);
	}

	SDL_Texture* loadTexture(string path)
	{
		return LoadTexture(path, Presenter::m_main_renderer);
	}
}