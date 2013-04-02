#include "Frame.h"
#include <iostream>
#include <string>
#include <climits>


long Frame::getTime(){
    return time;
}

void Frame::init(string fname, long newTime = LONG_MAX){
    initCount ++;
    cout<<"tag: "<<tag<<" initCount: "<<initCount;

    time = newTime;
    image = IMG_Load(fname.c_str());

    src.x = src.y = dest.x = dest.y = 0;
    src.w = dest.w = image->w;
    src.h = dest.h = image->h;
}

void Frame::draw(SDL_Surface *screen, int x, int y){    
    dest.x = x; dest.y = y;
    SDL_BlitSurface(image, &src, screen, &dest);
}

SDL_Rect Frame::getRect(){
    return dest;
}
Frame::Frame(){
    defaultCount++;
    tag = -1;
    time = 0;
    cout<<"tag: "<<tag<<" defaultCount: "<<defaultCount<<endl;
}
/*
Frame::Frame(string fname, long newTime = LONG_MAX){
    time = newTime;
    image = IMG_Load(fname.c_str());
    
    src.x = src.y = dest.x = dest.y = 0;
    src.w = dest.w = image->w;
    src.h = dest.h = image->h;
}
*/
 
Frame::~Frame(){
    if (image){
//        SDL_FreeSurface(image);
        image = NULL;
    }
}