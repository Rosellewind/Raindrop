#include "Frame.h"
#include <iostream>
#include <string>
#include <climits>


Frame::Frame(string fname, long newTime = LONG_MAX){
    time = newTime;
    image = IMG_Load(fname.c_str());
    
    src.x = src.y = dest.x = dest.y = 0;
    src.w = dest.w = image->w;
    src.h = dest.h = image->h;
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
    cout<<"deleting" <<image->w<<endl;
    SDL_FreeSurface(image);
    image = NULL;
}