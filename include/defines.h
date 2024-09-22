#pragma once

#include <iostream>
#include <string>

#include <vector>
#include <SDL.h>

using namespace std;

#define D(x) cerr << #x << " = " << (x) << " | " << __LINE__ << endl;
#define Dex(x) cerr << #x << " = " << (x) << " | " << __LINE__ << " " << __FILE__ << endl;
#define __FILE_NAME__ (strrchr(__FILE__, '\\' ) ? strrchr(__FILE__, '\\') + 1 : __FILE__)

static string CONFIG_FOLDER = "config\\";
static string IMG_FOLDER = "img\\";

struct int2 {
    int x = 0;
    int y = 0;
    int2(){}
    int2(int a, int b){
        x = a;
        y = b;
    }
};

struct float2{
    float x = 0;
    float y = 0;
};

struct double2 {
    double x = 0;
    double y = 0;
};

enum class SOUND
{
    NONE = 0,
    BACKGROUND = 1
};

struct Drawable {
    SDL_Texture* texture = nullptr;
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
};

enum class GameState {
    NONE = 0,
    MENU = 1,
    PLAYING = 2,
    ENDSCREEN = 3
};

struct Rect {
    double x, y;
    double w, h;
    SDL_Rect toSdlRect() {
        return { (int)x, (int)y, (int)w, (int)h };
    }
};

struct RotatedRect {
    Rect rect;
    double angle;
};