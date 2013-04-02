#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Frame.h"
#include "Animation.h"


Animation::Animation(string fname){
    int n;
    ifstream in(fname.c_str());
    in>>n;
    totalTime = 0;

    for (int i = 0; i<n; i++){
        long t;
        string f2name;
        in>>t>>f2name;
        totalTime += t;
        Frame *f = new Frame(f2name, t);
        frames.insert(frames.end(), f);
    }
    in.close();
}

void Animation::draw(SDL_Surface *screen, int x, int y, long elapsed){
    long currentFrameTime = elapsed % totalTime;
    for (int i = 0; i < frames.size(); i++) {        
        if (frames[i]->getTime() > currentFrameTime){
            frames[i]->draw(screen, x, y);
            break;
        }
        currentFrameTime -= frames[i]->getTime();
        
    }
}

SDL_Rect Animation::getRect(){
    return frames[0]->getRect();
}

Animation::~Animation(){
    for (int i = 0; i<frames.size(); i++) {
        delete frames[i];
    }
}