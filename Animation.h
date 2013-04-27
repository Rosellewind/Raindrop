#ifndef ANIMATION_H
#define ANIMATION_H

#ifdef _WIN32
#include "SDL/SDL.h"
#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

#elif __unix__
#include "SDL/SDL.h"
#endif

#include <vector>
#include "Frame.h"
using namespace std;////////////have 80 sdl_surface of the same images. change vector<Frame*> to a frame, position

class Animation{
    vector<Frame*> frames;
    Uint32 totalTime;
    bool isLoop;
public:
    Animation(string fname, bool isALoop = true);
    Animation(string fname, int column, bool isALoop);//for use with sprite sheet
    bool draw(SDL_Surface *screen, int x, int y, Uint32 elapsed);
    SDL_Rect getRect();
    ~Animation();
};

#endif