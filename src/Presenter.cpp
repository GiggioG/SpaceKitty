#include "Presenter.h"

#include "World.h"

extern World world;

SDL_Window* Presenter::m_main_window = nullptr;
SDL_Renderer* Presenter::m_main_renderer = nullptr;
int Presenter::m_SCREEN_WIDTH = 0;
int Presenter::m_SCREEN_HEIGHT = 0;

SDL_Renderer* Presenter::getRenderer()
{
    return m_main_renderer;
}

void Presenter::init()
{
    m_SCREEN_WIDTH = 1920;
    m_SCREEN_HEIGHT = 1080;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    m_main_window = SDL_CreateWindow("Space Kitty",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1366, 768, 0);
    m_main_renderer = SDL_CreateRenderer(m_main_window,
        -1, SDL_RENDERER_PRESENTVSYNC);
    improveRenderer();
}

void Presenter::improveRenderer()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    auto desktopWidth = DM.w;
    auto desktopHeight = DM.h;

    float2 mouseMultiply;
    mouseMultiply.x = (float)((double)m_SCREEN_WIDTH / (double)desktopWidth);
    mouseMultiply.y = (float)((double)m_SCREEN_HEIGHT / (double)desktopHeight);

    if (SDL_SetWindowFullscreen(m_main_window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
    {
        cout << "SDL_IMPROVE_RENDERER FAILED: %s\n" << SDL_GetError() << endl;
    }

    world.m_inputManager.setMouseMultiply(mouseMultiply);

    SDL_RenderSetLogicalSize(m_main_renderer, m_SCREEN_WIDTH, m_SCREEN_HEIGHT);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void Presenter::update(){
}

void Presenter::draw()
{
    SDL_RenderPresent(m_main_renderer);

    SDL_RenderClear(m_main_renderer);
}

void Presenter::drawObject(SDL_Texture* texture, int2 cameraPos = {0, 0}) {
    SDL_Rect movedBkgRect = {
        -cameraPos.x, -cameraPos.y,
        m_SCREEN_WIDTH, m_SCREEN_HEIGHT
    };
    SDL_RenderCopy(m_main_renderer, texture, NULL, &movedBkgRect);
}

void Presenter::drawObject(Drawable& drawable, int2 cameraPos = {0, 0}) {
    SDL_Rect movedRect = drawable.rect;
    movedRect.x -= cameraPos.x;
    movedRect.y -= cameraPos.y;
    double angleDegrees = drawable.angle * (180 / M_PI);
    SDL_RenderCopyEx(m_main_renderer, drawable.texture, NULL, &movedRect, angleDegrees, NULL, drawable.flip);
}