#include "Cup.h"
#include <vector>
#include <iostream>

string Type_String[] = {"plain", "color", "slow", "drain"};


Cup::Cup(string fname, vector<Animation*> colCups, Note n, int x):Sprite(n, fname, true, x, GAMESCREENHEIGHT-62){
    note = n;
    topOfCup = GAMESCREENHEIGHT - getRect().h;
    colorCups = colCups;
}

void Cup::update(Uint32 elapsed){
    Sprite::update(elapsed);
};

void Cup::raiseNote(){
    Note n;
    if (note == LC)
        n = D;
    else if (note == D)
        n = E;
    else if (note == E)
        n = F;
    else if (note == F)
        n = G;
    else if (note == G)
        n = A;
    else if (note == A)
        n = B;
    else if (note == B)
        n = HC;
    else
        n = LC;
    setToNote(n);
}

void Cup::setToNote(Note n){
    note = n;
    string newFile = "Resources/cups.txt";
    delete animation;
    animation = new Animation(newFile.c_str(),note,true);
}

void Cup::dragTo(int x, int y){
    xPos = (float)x - offsetX;
	yPos = topOfCup;
    int w = getRect().w;
    if (xPos < 0)
        xPos = 0;
    else if (xPos > SCREENWIDTH-w)
        xPos = SCREENWIDTH - w;
}

void Cup::draw(SDL_Surface *screen, Uint32 elapsed){
    Sprite::draw(screen, elapsed);
}

bool Cup::draw(SDL_Surface *screen, Uint32 elapsed, int noteClickedIndex){
    bool animate = false;
    if (noteClickedIndex == -1) {
        animation->draw(screen, xPos, yPos, elapsed);
    }
    else{
        animate = colorCups[noteClickedIndex]->draw(screen, xPos, yPos, elapsed);
    }
    return animate;
}

Cup::~Cup(){
    cout<<"...cup deconstructor..."<<endl;
    if(colorCups.size() > 0){
        for (unsigned int i = 0; i<colorCups.size(); i++){
            delete colorCups[i];
        }
        colorCups.clear();
    }
}

//class methods
vector<Cup*> Cup::initCups(int numCups, SDL_Surface *screen){
    
    //setup colorCups animations
    vector<Animation*> colorCups;
    for (int i = 0; i < 8; i++) {
        Animation *a = new Animation("Resources/colorCups.txt", i, false);
        colorCups.push_back(a);
    }
    
    //create cups
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
        Cup *c = new Cup("Resources/cups.txt", colorCups, LC, x);
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
                    if (drops[i]->type == PLAIN) {
                        cups[j]->raiseNote();
                    }
                }
            }
        }
    }
}


