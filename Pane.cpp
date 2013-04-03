#include <iostream>
#include "Pane.h"
#include "ProtoGame.h"

using namespace std;

Pane::Pane(){
    rect = {0,GAMESCREENHEIGHT,SCREENWIDTH,SCREENHEIGHT-GAMESCREENHEIGHT};
    
    //staticText eg.points, items, level
    Text *text1 = new Text("Points:", 0, GAMESCREENHEIGHT);
    Text *text2 = new Text("Items:", 0, GAMESCREENHEIGHT + 20);
    Text *text3 = new Text("Level:", SCREENWIDTH * .75, GAMESCREENHEIGHT);
    staticText.insert(staticText.end(), text1);
    staticText.insert(staticText.end(), text2);
    staticText.insert(staticText.end(), text3);
}
void Pane::draw(SDL_Surface *screen){
    
    //background
    SDL_FillRect(screen, &rect, 0x7F5217);
    
    //text
    for (int i = 0; i<staticText.size(); i++) {
        staticText[i]->draw(screen);
    }
}
Pane::~Pane(){
    for (int i = 0; i<staticText.size(); i++){
        delete staticText[i];
    }
}