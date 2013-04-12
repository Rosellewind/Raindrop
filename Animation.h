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
    bool isLoop;
public:
    Animation(string fname, bool isALoop = true);
    Animation(string fname, int column, bool isALoop);//for use with sprite sheet
    bool draw(SDL_Surface *screen, int x, int y, long elapsed);
    SDL_Rect getRect();
    ~Animation();
};

#endif