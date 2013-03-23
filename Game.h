#ifndef GAME_H
#define GAME_H

#ifdef _WIN32
#include "SDL/SDL.h"
#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#endif

#include <vector>
#include <string>
#include "Sprite.h"
#include "Drop.h"
#include "Cup.h"

class Game{
protected:
    SDL_Surface *screen;
    bool done;
    vector<Sprite*> sprites;
public:
    virtual void init(string fname);
    void run();
};

#endif
