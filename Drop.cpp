#include "Drop.h"
#include "ProtoGame.h"

Drop::Drop(string fname, Type type, int x, int gameSpeed): Sprite(0, fname, true, x, 0, 0, gameSpeed){
    isCaught = 0;
}

void Drop::update(Uint32 elapsed){
    Sprite::update(elapsed);
}

bool Drop::isAlive(){
    if (isCaught)
        return yPos < GAMESCREENHEIGHT - 60;
    else
        return yPos < GAMESCREENHEIGHT - 20;
}





