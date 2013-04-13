#include <iostream>
#include <string>
#include "Pane.h"
#include <sstream>
#include "Functions.h"
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
    
    //pool
    pool = new Animation("ltBluePool.txt");
    SDL_Rect tempRect = pool->getRect();
    poolRect = {static_cast<Sint16>(rect.w/2 - tempRect.w/2), static_cast<Sint16>(rect.h/2 - tempRect.h/2 + rect.y), tempRect.w, tempRect.h};
    cout<<poolRect.x<<" "<<poolRect.y<<" "<<poolRect.w<<" "<<poolRect.h<<endl;
}

void Pane::updatePoints(int points){
	string newText = NTS(points);
    pointsText->updateText(newText);
}

void Pane::updateLevel(int level){
	string newText = NTS(level);
    levelText->updateText(newText);
}

void Pane::flashColor(Note note){/////////change to update instead on delete/new
    string newFile = Note_String[note] + "Pool.txt";

    delete pool;
    pool = new Animation(newFile);
}

void Pane::draw(SDL_Surface *screen, long elapsed){
    
    //background
    Uint32 color32bit = SDL_MapRGB(screen->format, 66, 54, 48);

    SDL_FillRect(screen, &rect, color32bit);
    
    //text
    for (int i = 0; i<staticText.size(); i++) {
        staticText[i]->draw(screen);
    }
    pointsText->draw(screen);
    levelText->draw(screen);
    pool->draw(screen, poolRect.x, poolRect.y, elapsed);
}

Pane::~Pane(){
    for (int i = 0; i<staticText.size(); i++){
        delete staticText[i];
    }
}
