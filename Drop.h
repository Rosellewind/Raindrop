#ifndef DROP_H
#define DROP_H

#include "Sprite.h"
#include "ProtoGame.h"

class Drop: public Sprite{
public:
    Type type;
    bool isCaught;
    
    void init(string fname, Type type, int x, int gameSpeed);
    void update(long elapsed);
    bool isAlive();
};

#endif