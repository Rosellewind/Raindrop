#ifndef DROP_H
#define DROP_H

#include "Sprite.h"
#include "ProtoGame.h"

class Drop : public Sprite{
public:
    Type type;
    bool isCaught;
    Note note;
    
    Drop(string fname, Type kind, int x, int gameSpeed, Note n = LC);
    void update(Uint32 elapsed);
    bool isAlive();
    void setIsCaught(bool caught);
};

#endif