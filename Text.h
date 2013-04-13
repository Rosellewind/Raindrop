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
#endif

#include <string>

using namespace std;


class Text {
    SDL_Surface *textSurface;
    SDL_Rect rect;
    TTF_Font *font;
    SDL_Color textColor;
public:
    Text(string textString, int x, int y, string fontName = "Arial.ttf", int fontSize = 28, SDL_Color txtColor = { 255, 255, 255 });
    void updateText(string newText);
    void draw(SDL_Surface *screen);
    SDL_Rect getRect();
    ~Text();
};




#endif
