#ifndef CUP_H
#define CUP_H

#include "Sprite.h"
#include "ProtoGame.h"
#include "Drop.h"
class Cup : public Sprite{
public:
    
    Note note;
    void update(Uint32 elapsed);
    void raiseNote();
    int topOfCup;
    vector<Animation*> colorCups;
    
    Cup(string fname, vector<Animation*> colCups, Note n = LC, int x = 0);
    void setToNote(Note n);
    void dragTo(int x, int y);
    void draw(SDL_Surface *screen, Uint32 elapsed);
    bool draw(SDL_Surface *screen, Uint32 elapsed, int noteClickedIndex);
    ~Cup();

    //class methods
    static vector<Cup*> initCups(int numCups, SDL_Surface*screen);
    static void checkCollisions(vector<Cup*> cups, vector<Drop*> drops);
};

#endif