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
using namespace std;

class Animation{
    Frame *frame;
    Uint32 totalTime;
    bool isLoop;
    int column, columns, rows, width, height;
    vector<int> times;

public:
    Animation(string fname, int col, bool isALoop);
    bool draw(SDL_Surface *screen, int x, int y, Uint32 elapsed);
    SDL_Rect getRect();
    ~Animation();
};

#endif
