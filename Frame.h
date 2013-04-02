#ifndef FRAME_H
#define FRAME_H

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL_image/SDL_image.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#endif

#include <string>

using namespace std;
static int defaultCount = 0;
static int initCount = 0;
class Frame{

    int tag;
    SDL_Surface *image;
    SDL_Rect src, dest;
    long time;
public:
    long getTime();
    void init(string fname, long newTime);
    void draw(SDL_Surface *screen, int x, int y);
    SDL_Rect getRect();
    Frame();
    ~Frame();
};

#endif
