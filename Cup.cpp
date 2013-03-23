#include "Cup.h"
#include <vector>
#include <iostream>

string Note_String[] = {"lc", "d", "e", "f", "g", "a", "b", "hc"};
string Type_String[] = {"plain", "color", "slow", "drain"};

void Cup::update(long elapsed){
    Sprite::update(elapsed);
};

void Cup::raiseNote(){
    if (note == LC)
        note = D;
    else if (note == D)
        note = E;
    else if (note == E)
        note = F;
    else if (note == F)
        note = G;
    else if (note == G)
        note = A;
    else if (note == A)
        note = B;
    else if (note == B)
        note = HC;
    else if (note == HC)
        note = LC;
    string newFile = Note_String[note] + "Cup.txt";
    delete animation;
    animation = new Animation;
    animation->init(newFile.c_str());
}

void Cup::init(string fname, Note n, int x){
    Sprite::init(fname, x, GAMESCREENHEIGHT-62);
    note = n;
    topOfCup = GAMESCREENHEIGHT - getRect().h;
}

vector<Cup*> Cup::initCups(int numCups, SDL_Surface *screen){
    vector<Cup*> cups(numCups);
    for (int i = 0; i<numCups; i++) {
        Cup *c = new Cup();
        int x = (rand()%10)*0.1*SCREENWIDTH;
        c->init("lcCup.txt", LC, x);
        cups[i] = c;
    }
    return cups;
}

void Cup::checkCollisions(vector<Cup*> cups, vector<Drop*> drops){
    for (int i = 0; i < drops.size(); i++) {
        SDL_Rect dropRect = drops[i]->getRect();
        int topOfCups = 0;
        if (cups.size()>0) 
            topOfCups = cups[0]->topOfCup;
        if (dropRect.y + dropRect.h > topOfCups && !drops[i]->isCaught){
            for (int j = 0; j < cups.size(); j++) {
                if (cups[j]->checkCollisionByCenter(dropRect)){
                    drops[i]->isCaught = 1;
                    cups[j]->raiseNote();
                }
            }
        }
    }
}

void Cup::dragTo(int x, int y){
    //    Sprite::dragTo(x, topOfCup);
    xPos = (float)x - offsetX;
	yPos = topOfCup;
}

