#ifndef CUP_H
#define CUP_H

#include "Sprite.h"
#include "ProtoGame.h"
#include "Drop.h"
class Cup: public Sprite{
public:
    
    Note note;
    void update(long elapsed);
    void raiseNote();
    int topOfCup;
    
    void init(string fname, Note n = LC, int x = 0);
    void dragTo(int x, int y);
    static vector<Cup*> initCups(int numCups, SDL_Surface*screen);
    static void checkCollisions(vector<Cup*> cups, vector<Drop*> drops);
};

#endif