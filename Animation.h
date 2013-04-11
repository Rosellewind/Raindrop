#ifndef ANIMATION_H
#define ANIMATION_H

#ifdef _WIN32
#include "SDL/SDL.h"
#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

#elif __unix__
#endif

#include <vector>
#include "Frame.h"
using namespace std;

class Animation{
    vector<Frame*> frames;
    long totalTime;
public:
    Animation(string fname);
    Animation(string fname, int column);//for use with sprite sheet
    void draw(SDL_Surface *screen, int x, int y, long elapsed);
    SDL_Rect getRect();
    ~Animation();
};

#endif