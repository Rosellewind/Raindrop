#include "Cup.h"
#include <vector>
#include <iostream>

string Type_String[] = {"plain", "color", "slow", "drain"};


Cup::Cup(string fname, Note n, int x):Sprite(n, fname, true, x, GAMESCREENHEIGHT-62){
    note = n;
    topOfCup = GAMESCREENHEIGHT - getRect().h;
}

void Cup::update(Uint32 elapsed){
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
    string newFile = "Resources/cups.txt";
    delete animation;
    animation = new Animation(newFile.c_str(),note,true);
}

void Cup::dragTo(int x, int y){
    xPos = (float)x - offsetX;
	yPos = topOfCup;
}

//class methods
vector<Cup*> Cup::initCups(int numCups, SDL_Surface *screen){
    vector<int> xtaken;
    vector<Cup*> cups(numCups);
    for (int i = 0; i<numCups; i++) {
        int x = (rand()%10)*0.1*SCREENWIDTH;
        for (int n = 0; n<xtaken.size(); n++){
            if(xtaken[n] == x){
                i--;
                break;
            }
        }
        xtaken.push_back(x);
        Cup *c = new Cup("Resources/cups.txt", LC, x);
        cups[i] = c;
    }
    return cups;
}

void Cup::checkCollisions(vector<Cup*> cups, vector<Drop*> drops){
    for (unsigned int i = 0; i < drops.size(); i++) {
        SDL_Rect dropRect = drops[i]->getRect();
        int topOfCups = 0;
        if (cups.size()>0)
            topOfCups = cups[0]->topOfCup;
        if (dropRect.y + dropRect.h > topOfCups && !drops[i]->isCaught){
            for (unsigned int j = 0; j < cups.size(); j++) {
                if (cups[j]->checkCollisionByCenter(dropRect)){
                    drops[i]->isCaught = 1;
                    cups[j]->raiseNote();
                }
            }
        }
    }
}


