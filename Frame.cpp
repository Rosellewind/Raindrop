#include "Frame.h"
#include <iostream>
#include <string>
#include <fstream>


Frame::Frame(string imageName, int x, int y, int w, int h, Uint32 newTime){
    time = newTime;
    image = IMG_Load(imageName.c_str());
    tag = 0;
    src.x = x; src.y = y; dest.x = dest.y = 0;
    src.w = w; dest.w = w;
    src.h = h; dest.h = h;
}

Frame::Frame(string fname, int column, int row){
    int columns, rows, width, height;
    string imageName;
    ifstream in(fname.c_str());
    in>>columns>>rows>>width>>height>>imageName;
    tag = 0;
    if (column < columns && row < rows) {
        int x = column * width;
        int y = row * height;
        time = 100;
        image = IMG_Load(imageName.c_str());
        src.x = x; src.y = y; dest.x = dest.y = 0;
        src.w = width; dest.w = width;
        src.h = height; dest.h = height;
    }
    in.close();
}


Uint32 Frame::getTime(){
    return time;
}

void Frame::draw(SDL_Surface *screen, int x, int y, int sx, int sy){
    dest.x = x; dest.y = y;
    if (sx != -1){src.x = sx, src.y = sy;}
    SDL_BlitSurface(image, &src, screen, &dest);
}

SDL_Rect Frame::getRect(){
    return dest;
}

Frame::~Frame(){
    SDL_FreeSurface(image);
    image = NULL;
}