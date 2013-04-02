#include "Pane.h"
#include "ProtoGame.h"
Pane::Pane(){
    rect = {0,GAMESCREENHEIGHT,SCREENWIDTH,SCREENHEIGHT-GAMESCREENHEIGHT};
}
void Pane::draw(SDL_Surface *screen){
    //background
    SDL_FillRect(screen, &rect, 0x7F5217);
    
    //points, items, level
    
}