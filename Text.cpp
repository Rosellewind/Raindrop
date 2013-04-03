#include "Text.h"
#include "ProtoGame.h"

#include <iostream>

Text::Text(string textString, int x, int y, string fontName, int fontSize, SDL_Color textColor){
    if( TTF_Init() < 0)
        cout<<"tff init error"<<endl;
    TTF_Font *font = TTF_OpenFont(fontName.c_str(), fontSize);
    textSurface = TTF_RenderText_Solid(font, textString.c_str(), textColor);
    rect.x = x;
    rect.y = y * -1;
    rect.w = textSurface->w;
    rect.h = y + textSurface->h;//////////////
}

void Text::draw(SDL_Surface *screen)
{
    SDL_BlitSurface(textSurface, &rect, screen, NULL);
}

Text::~Text(){
    SDL_FreeSurface(textSurface);
}