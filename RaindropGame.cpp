#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Sprite.h"
#include "Animation.h"
#include "ProtoGame.h"
#include "RaindropGame.h"
#include "Game.h"

void RaindropGame::init(string fname, int cups, int drops, int speed, int latency){
    Game::init(fname);
    gameSpeed = speed;
    numCups = cups;
    numDrops = drops;
    minLatency = latency;
    isDragging = false;
    timestampMouseDown = 0;
    objDragged = NULL;
}

void RaindropGame::run(){
    SDL_Event event;
    long last = SDL_GetTicks();
    SDL_Delay(100);
    
    //add cups
    cups = Cup::initCups(numCups, screen);
    
    
    //run loop
    while (!done) {
        long elapsed = SDL_GetTicks();
        
        //add drops if needed
        while (drops.size() < numDrops && elapsed > last + minLatency) {
            Drop *d = new Drop;
            int x = (rand()%20)*0.05*SCREENWIDTH;
            d->init("a.txt", PLAIN, x, gameSpeed);
            drops.insert(drops.end(), d);
            last = SDL_GetTicks();
        }
        
        //erase drops that are going offscreen
        for (int i = (int)drops.size()-1; i >= 0; i--) {
            if (drops[i]->isAlive() == 0) {
                Drop *d = drops[i];
                drops.erase(drops.begin()+i);
//                cout<<"game image->w"<<d->animation->frames[0]->image->w;
                delete d;
            }
        }//for all, for each, algorithms part
        
        //events loop
        while (SDL_PollEvent(&event)){//checks events one at a time
			switch( event.type ){
				case SDL_QUIT: done = true; break;
				case SDL_MOUSEBUTTONUP: 
					timestampMouseDown = 0;
					if(isDragging){
                        objDragged->stopDragging();
                        isDragging = false;
                        objDragged = NULL;
					}
					else{
						int x = event.button.x; int y = event.button.y;
						//check to see if it is on click/draggable object
						if (checkClickCup(x, y)) {
							;//audioPlayer.playNote(cup->note);, need cup         
						}
                    }
					break;
				case SDL_MOUSEBUTTONDOWN: {
					timestampMouseDown = SDL_GetTicks(); //////////////////
                    int x = event.button.x; int y = event.button.y;
					if (checkClickCup(x, y)) 
						setDraggedObject(x, y);}//brackets are needed because of declaring variables and needing scope
					break;
				case SDL_MOUSEMOTION: 
					if(timestampMouseDown){
						long now = SDL_GetTicks();
						if (now - timestampMouseDown > 10 && objDragged){/////
							isDragging = true;
							int x = event.motion.x; int y = event.motion.y;
							objDragged->dragTo(x,y);
						}
					}
                    break;
                default:
                    cout<<"other event"<<endl;
			}//ends event.type switch
        }//ends event detection while loop
        
        
        //check for collisions and update if needed
        Cup::checkCollisions(cups,drops);
        
        //update background
        for (int i = 0; i < sprites.size(); i++) {
            sprites[i]->update(elapsed);
            sprites[i]->draw(screen, elapsed);
        }
        
        //update drops
        for (int i = 0; i < drops.size(); i++) {
            drops[i]->update(elapsed);
            drops[i]->draw(screen, elapsed);
        }
        
        //update cups
        for (int i = 0; i < cups.size(); i++) {
            cups[i]->update(elapsed);
            cups[i]->draw(screen, elapsed);
        }
        SDL_Flip(screen);
    }//while !done loop ends
    
    SDL_Quit();
     
}//run ends

void RaindropGame::setDraggedObject(int x, int y){
    bool found = 0;
    while (!found) {
        for (int i = 0; i < cups.size(); i++) {
            SDL_Rect cupRect = cups[i]->getRect();
            if( ( x > cupRect.x ) && ( x < cupRect.x + cupRect.w ) && ( y > cupRect.y ) && ( y < cupRect.y + cupRect.h ) ){
                objDragged = cups[i];
                objDragged->startDragging(x,y);
                found = 1;
                break;
            }
        }
        //add for other obj that can be dragged
    }
    
}

bool RaindropGame::checkClickCup(int x, int y){
    for(int i = 0; i<cups.size();i++){
        SDL_Rect cupRect = cups[i]->getRect();
        if( ( x > cupRect.x ) && ( x < cupRect.x + cupRect.w ) && ( y > cupRect.y ) && ( y < cupRect.y + cupRect.h ) )
            return 1;
    }
    return 0;
}


