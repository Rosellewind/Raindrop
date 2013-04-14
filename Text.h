#ifndef TEXT_H
#define TEXT_H

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>

#elif __unix__
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#endif

#include <string>

using namespace std;


class Text{
    SDL_Surface *textSurface;
    SDL_Rect rect;
    TTF_Font *font;
    SDL_Color textColor;
public:
    Text(string textString, int x, int y); //moved inits into constructor JaredTS
    void updateText(string newText);
    void draw(SDL_Surface *screen);
    SDL_Rect getRect();
    ~Text();
};




#endif
