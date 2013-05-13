#include "Drop.h"
#include "ProtoGame.h"

Drop::Drop(string fname, Type kind, int x, int gameSpeed, Note n): Sprite(n, fname, true, x, 0, 0, gameSpeed){
    type = kind;
    isCaught = 0;
    note = n;
}

void Drop::update(Uint32 elapsed){
    Sprite::update(elapsed);
}

bool Drop::isAlive(){
    bool alive = false;
    if (type == PLAIN && isCaught)
        alive = yPos < GAMESCREENHEIGHT - 60;
    else if (type == PLAIN && !isCaught)
        alive = yPos < GAMESCREENHEIGHT - 20;
    else if (type == COLOR && isCaught)
        alive = yPos < GAMESCREENHEIGHT - 70;
    else if (type == COLOR && !isCaught)
        alive = yPos < GAMESCREENHEIGHT - 30;
    return alive;
}

void Drop::setIsCaught(bool caught){
    isCaught = caught;
    if (type == COLOR){

    }
}






