#include "Drop.h"
#include "ProtoGame.h"

Drop::Drop(string fname, Type type, int x, int gameSpeed): Sprite(fname, x, 0, 0, gameSpeed){
    isCaught = 0;
    // Member "type" should also be initialized here if possible, not sure what to init -- JaredTS
}

void Drop::update(Uint32 elapsed)
{
    Sprite::update(elapsed);
}

bool Drop::isAlive()
{
    if (isCaught) 
        return yPos < GAMESCREENHEIGHT - 60;
    else 
        return yPos < GAMESCREENHEIGHT - 20;
}





