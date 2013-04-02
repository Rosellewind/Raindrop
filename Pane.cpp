#include <iostream>
#include "Pane.h"
#include "ProtoGame.h"

using namespace std;

Pane::Pane(){
    rect = {0,GAMESCREENHEIGHT,SCREENWIDTH,SCREENHEIGHT-GAMESCREENHEIGHT};
}
void Pane::draw(SDL_Surface *screen){
    
    //background
    SDL_FillRect(screen, &rect, 0x7F5217);
    
    //points, items, level
    TTF_Font *font = NULL;
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface *text;
    font = TTF_OpenFont( "lazy.ttf", 28 );
    text = TTF_RenderText_Solid( font, "The quick brown fox jumps over the lazy dog", textColor );

    if( TTF_Init() < 0)
        cout<<"tff init error"<<endl;
    font = TTF_OpenFont( "lazy.ttf", 28);
    applySurface(0, GAMESCREENHEIGHT, text, screen);

    
}

void Pane::applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}