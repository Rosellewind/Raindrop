#include "Frame.h"
#include <iostream>
#include <string>


Frame::Frame(string fname, long newTime){
    time = newTime;
    image = IMG_Load(fname.c_str());
    
    src.x = src.y = dest.x = dest.y = 0;///////////////////
    src.w = dest.w = image->w;
    src.h = dest.h = image->h;
}

Frame::Frame(string fname, int x, int y, int w, int h, long newTime){
    time = newTime;
    image = IMG_Load(fname.c_str());
    
    src.x = x; src.y = y; dest.x = dest.y = 0;
    src.w = w; dest.w = w;
    src.h = h; dest.h = h;
}

long Frame::getTime(){
    return time;
}

void Frame::draw(SDL_Surface *screen, int x, int y){    
    dest.x = x; dest.y = y;
    SDL_BlitSurface(image, &src, screen, &dest);
}

SDL_Rect Frame::getRect(){
    return dest;
}
 
Frame::~Frame(){
    SDL_FreeSurface(image);
    image = NULL;
}