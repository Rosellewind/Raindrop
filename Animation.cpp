#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Frame.h"
#include "Animation.h"

Animation::Animation(string fname, bool isALoop){//get which animation
    totalTime = 0;
    int n;
    ifstream in(fname.c_str());
    in>>n;
    isLoop = isALoop;

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

Animation::Animation(string fname, int column, bool isALoop){
    totalTime = 0;
    int columns, rows, width, height;
    string imageName;
    ifstream in(fname.c_str());
    in>>columns>>rows>>width>>height>>imageName;
    isLoop = isALoop;

    if (column < columns) {
        int x = column * width;
        int y = 0;
        for (int i = 0; i<rows; i++){
            long t;
            in>>t;
            totalTime += t;
            Frame *f = new Frame(imageName, x, y, width, height, totalTime);
            frames.insert(frames.end(), f);
            y += height;
        }
    }
    else cout<<"error in animation"<<endl;
    in.close();
}
bool Animation::draw(SDL_Surface *screen, int x, int y, long elapsed){
    bool stop = false;
    cout<<totalTime<<endl;
    if (totalTime == 0) totalTime++;
    long currentFrameTime = elapsed % totalTime;               //currentFrameTime 0 - 1000
     for (int i = 0; i < frames.size(); i++) {
         if (frames[i]->getTime() <= currentFrameTime){          //getTime gives 100, 200, etc
             cout<<"getTime: "<<frames[i]->getTime()<<endl;
             frames[i]->draw(screen, x, y);
             if (!isLoop)cout<<"drawing"<<endl;

             if (!isLoop && i == frames.size()-1){
             stop = true;
             }
             break;
         }
//         currentFrameTime -= frames[i]->getTime();
     }
     return stop;
 }
 /*
void Animation::draw(SDL_Surface *screen, int x, int y, long elapsed){
    long currentFrameTime = elapsed % totalTime;
    for (int i = 0; i < frames.size(); i++) {        
        if (frames[i]->getTime() > currentFrameTime){
            frames[i]->draw(screen, x, y);
        }
        currentFrameTime -= frames[i]->getTime();
        
    }
}
*/
SDL_Rect Animation::getRect(){
    return frames[0]->getRect();
}

Animation::~Animation(){
    for (int i = 0; i<frames.size(); i++) {
        delete frames[i];
    }
}
