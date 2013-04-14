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
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#endif

#include <string>
#include <climits>

#define UINT32_MAX  (0xffffffff)
using namespace std;
class Frame{
    int tag;
    SDL_Surface *image;
    SDL_Rect src, dest;
    Uint32 time;
public: 
    Frame(string imageName, Uint32 newTime = UINT32_MAX);
    Frame(string imageName, int x, int y, int w, int h, Uint32 newTime);//for use with animation sprite sheet
    Frame(string fname, int column, int row);//for single image from sprite sheet
    Uint32 getTime();
    void draw(SDL_Surface *screen, int x, int y);
    SDL_Rect getRect();
    ~Frame();
};

#endif
