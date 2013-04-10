#include <iostream>
#include "Pane.h"
#include "ProtoGame.h"

using namespace std;

Pane::Pane(){
    rect = {0,GAMESCREENHEIGHT,SCREENWIDTH,SCREENHEIGHT-GAMESCREENHEIGHT};
    paneColor.r = 66;
    paneColor.g = 54;
    paneColor.b = 48;
    int pad = 6;
    
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
    
     
}

void Pane::updatePoints(int points){
    string newText = to_string(points);
    pointsText->updateText(newText);
}

void Pane::updateLevel(int level){
    string newText = to_string(level);
    levelText->updateText(newText);
}

void Pane::draw(SDL_Surface *screen){///////change to just update changes

    //background
    Uint32 color32bit = SDL_MapRGB(screen->format, 66, 54, 48);

    SDL_FillRect(screen, &rect, color32bit);
    
    //text
    for (int i = 0; i<staticText.size(); i++) {
        staticText[i]->draw(screen);
    }
    pointsText->draw(screen);
    levelText->draw(screen);
}

Pane::~Pane(){
    for (int i = 0; i<staticText.size(); i++){
        delete staticText[i];
    }
}