#ifndef PANE_H
#define PANE_H

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL_ttf/SDL_ttf.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>

#elif __unix__
#endif

#include <vector>
#include "Text.h"

using namespace std;
class Pane{
    SDL_Rect rect;
    vector<Text*> staticText;
    //    pool;
    
public:
    Pane();
    void draw(SDL_Surface *screen);
    ~Pane();
};

#endif
