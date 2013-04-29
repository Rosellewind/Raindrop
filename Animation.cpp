#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Frame.h"
#include "Animation.h"


Animation::Animation(string fname, int col, bool isALoop){
    totalTime = 0;
    string imageName;
    ifstream in(fname.c_str());
    in>>columns>>rows>>width>>height>>imageName;
    column = col;
    isLoop = isALoop;
    
    if (column < columns) {
        frame = new Frame(imageName.c_str(), 0, 0, width, height, totalTime);
        for (int i = 0; i<rows; i++){
            Uint32 t;
            in>>t;
            totalTime += t;
            times.push_back(totalTime);
        }
    }
    else cout<<"error in animation"<<endl;
    in.close();
}

bool Animation::draw(SDL_Surface *screen, int x, int y, Uint32 elapsed){
    bool animate = true;
    if (totalTime == 0) totalTime = -1;
    Uint32 currentFrameTime = elapsed % totalTime;
    
    int min = 0;
    for (unsigned int i = 0; i < times.size(); i++){
        if (i != 0)
            min = times[i-1];
        if (currentFrameTime >= min && currentFrameTime < times[i]){
            frame->draw(screen, x, y, column*width, i*height);
            if (!isLoop && i == times.size()-1){
                animate = false;
            }
            break;
        }
    }
    return animate;
}

SDL_Rect Animation::getRect(){
    return frame->getRect();
}

Animation::~Animation(){
    delete frame;
}
