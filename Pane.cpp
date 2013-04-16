#include <iostream>
#include <string>
#include "Pane.h"
#include <sstream>
#include "Functions.h"

using namespace std;

Pane::Pane(){
    rect = {0,GAMESCREENHEIGHT,SCREENWIDTH,SCREENHEIGHT-GAMESCREENHEIGHT};
    int pad = 6;
    poolIndex = -1;
    
    //staticText
    Text *text1 = new Text("Points: ", pad, rect.y + pad/2);
    Text *text2 = new Text("Items: ", pad, rect.y + rect.h/3 + pad/2);
    Text *text3 = new Text("Level: ", rect.w * .8, rect.y + pad/2);
    staticText.insert(staticText.end(), text1);
    staticText.insert(staticText.end(), text2);
    staticText.insert(staticText.end(), text3);
    
    //dynamicText
    SDL_Rect rect1 = text1->getRect();
    pointsText = new Text("0", rect1.x + rect1.w, rect1.y);
    SDL_Rect rect2 = text3->getRect();
    levelText = new Text("1", rect2.x + rect2.w, rect2.y);
    
    //pool, static frame and array for animations
    pool = new Frame("Resources/pools.txt", 8, 2);
    SDL_Rect tempRect = pool->getRect();
    poolRect = {static_cast<Sint16>(rect.w/2 - tempRect.w/2), static_cast<Sint16>(rect.h/2 - tempRect.h/2 + rect.y), tempRect.w, tempRect.h};
    for (int i = 0; i < 9; i++) {
        Animation *a = new Animation("Resources/pools.txt", i, false);
        pools.push_back(a);
    }
}

void Pane::updatePoints(int points){
	string newText = NTS(points);
    pointsText->updateText(newText);
}

void Pane::updateLevel(int level){
	string newText = NTS(level);
    levelText->updateText(newText);
}

void Pane::flashColor(Note note){
        poolIndex = note;
}

void Pane::draw(SDL_Surface *screen, Uint32 elapsed){
    
    //background
    Uint32 color32bit = SDL_MapRGB(screen->format, 66, 54, 48);
    SDL_FillRect(screen, &rect, color32bit);
    
    //text
    for (int i = 0; i<staticText.size(); i++) {
        staticText[i]->draw(screen);
    }
    pointsText->draw(screen);
    levelText->draw(screen);
    
    //pool
    if (poolIndex == -1) {
        pool->draw(screen, poolRect.x, poolRect.y);
    }
    else{
        bool animate = pools[poolIndex]->draw(screen, poolRect.x, poolRect.y, elapsed);
        if (!animate)
            poolIndex = -1;
    }
}

Pane::~Pane(){
    for (unsigned int i = 0; i<staticText.size(); i++){
        delete staticText[i];
    }
    if (pointsText) delete pointsText;
    if (levelText) delete levelText;
    for (unsigned int i = 0; i < pools.size(); i++) {
        ;//delete pools[i];
    }
}
