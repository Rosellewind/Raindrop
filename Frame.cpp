#include "Frame.h"
#include <iostream>
#include <string>
#include <fstream>


Frame::Frame(string imageName, long newTime){
    time = newTime;
    image = IMG_Load(imageName.c_str());
    
    src.x = src.y = dest.x = dest.y = 0;///////////////////
    src.w = dest.w = image->w;
    src.h = dest.h = image->h;
}

Frame::Frame(string imageName, int x, int y, int w, int h, long newTime){
    time = newTime;
    image = IMG_Load(imageName.c_str());
    
    src.x = x; src.y = y; dest.x = dest.y = 0;
    src.w = w; dest.w = w;
    src.h = h; dest.h = h;
}

Frame::Frame(string fname, int column, int row){//need time?
    int columns, rows, width, height;
    string imageName;
    ifstream in(fname.c_str());
    in>>columns>>rows>>width>>height>>imageName;
    
    if (column < columns && row < rows) {
        int x = column * width;
        int y = row * height;
        time = LONG_MAX;
        image = IMG_Load(imageName.c_str());
        src.x = x; src.y = y; dest.x = dest.y = 0;
        src.w = width; dest.w = width;
        src.h = height; dest.h = height;
    }
    in.close();
}


long Frame::getTime(){
    return time;
}

void Frame::draw(SDL_Surface *screen, int x, int y){    
    dest.x = x; dest.y = y;
    SDL_BlitSurface(image, &src, screen, &dest);
}

SDL_Rect Frame::getRect(){
//    cout<<"rect: "<<dest.x<<" "<<dest.y<<" "<<dest.w<<" "<<dest.h<<" "<<endl;
    return dest;
}
 
Frame::~Frame(){
    SDL_FreeSurface(image);
    image = NULL;
}