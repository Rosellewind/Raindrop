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
    void init(string fname);
    void draw(SDL_Surface *screen, int x, int y, long elapsed);
    SDL_Rect getRect();
};

#endif