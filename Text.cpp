#include "Text.h"
#include "ProtoGame.h"

#include <iostream>

Text::Text(string textString, int x, int y, string fontName, int fontSize, SDL_Color txtColor){
    if( TTF_Init() < 0)
        cout<<"tff init error"<<endl;
    atexit(TTF_Quit);
    textColor = txtColor;
    font = TTF_OpenFont(fontName.c_str(), fontSize);///no font
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        // handle error
    }
    textSurface = TTF_RenderText_Blended(font, textString.c_str(), textColor);
    rect = {static_cast<Sint16>(x),static_cast<Sint16>(y),static_cast<Uint16>(textSurface->w),static_cast<Uint16>(textSurface->h)};
}

void Text::updateText(string newText){
    SDL_FreeSurface(textSurface);
    textSurface = TTF_RenderText_Blended(font, newText.c_str(), textColor);
}

void Text::draw(SDL_Surface *screen)
{
    SDL_BlitSurface(textSurface, NULL, screen, &rect);
}

SDL_Rect Text::getRect()
{
    return rect;
}

Text::~Text(){
    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);
}