#ifndef FRAME_H
#define FRAME_H

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#endif

#include <string>
#include <climits>

using namespace std;


class Frame{

    int tag;
    SDL_Surface *image;
    SDL_Rect src, dest;
    long time;
public:
    Frame(string fname, long newTime = LONG_MAX);
    Frame(string fname, int x, int y, int w, int h, long newTime);//for use with sprite sheet
    long getTime();
    void draw(SDL_Surface *screen, int x, int y);
    SDL_Rect getRect();
    ~Frame();
};

#endif
