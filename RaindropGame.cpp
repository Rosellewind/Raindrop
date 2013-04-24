#include <iostream>
#include <fstream>
#include <ctime>
#include "Animation.h"
#include "ProtoGame.h"
#include "RaindropGame.h"

using namespace std;

RaindropGame::RaindropGame(string fname, int cups, int drops, int speed, int latency, int lvl):Game(fname){
    gameSpeed = speed;
    numCups = cups;
    numDrops = drops;
    minLatency = latency;
    isDragging = false;
    timestampMouseDown = 0;
    objDragged = NULL;
    noteClickedIndex = -1;
    
    //set background
    background = new Sprite("Resources/background.txt");
    backgrounds.insert(backgrounds.begin(), background);
    
    //set pane
    pane = new Pane();
    
    //setup sound
    soundplayer = new SoundPlayer(pane);
    soundplayer->init(44100, 2, 4096);
    soundplayer->load_sounds("Resources/audio.txt");
    
    //gameManager
    gameManager = new GameManager(lvl, pane, soundplayer);
    
    //seed psuedo random number generator
    srand ((unsigned int)time(NULL));
}

void RaindropGame::run(){
    SDL_Event event;
    last = SDL_GetTicks();
    lastDrop = last;
    SDL_Delay(100);
    
    //JaredTemp 2. make sprites
    for (int i = 0; i<20; i++) {
        int r = (rand()%20)*0.05*SCREENWIDTH;//use # of drops that will fit, prevents overlap, then disperse over the % of the screen,ex. 100/20 = 5%
        Sprite *drop = new Sprite(0,"Resources/tempDrops.txt", true, r, r, r, r);
        tempDrops.push_back(drop);
    }

    //add cups
    cups = Cup::initCups(numCups, screen);
    
    //play sound
    soundplayer->setMusicVolume(15);
    soundplayer->playMusic();
    
    //play sound pattern
    soundplayer->playNoteSequence(gameManager->getPattern(), 6000);
    
    //run loop
    while (!done) {
        elapsed = SDL_GetTicks();
        if(1000/100 > (elapsed-last))
			SDL_Delay(1000/60 - (elapsed-last)); //RESTRICT PLAYBACK TO 60 FRAMES A SECOND
        last = elapsed;
        
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
                            soundplayer->pauseNoteSequence(2000);
                            soundplayer->playSound(objDragged->note, SoundPlayer::CLICK_CHANNEL);
                            pane->flashColor(objDragged->note);
						}
                    }
					break;
				case SDL_MOUSEBUTTONDOWN: {
					timestampMouseDown = SDL_GetTicks(); //////////////////
                    int x = event.button.x; int y = event.button.y;
					if (checkClickCup(x, y))
						setDraggedObject(x, y);}
					break;
				case SDL_MOUSEMOTION:
					if(timestampMouseDown){
						Uint32 now = SDL_GetTicks();
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
        
        
        //check for water in cup and update if needed
        Cup::checkCollisions(cups,drops);
        
        //update background, drops, cups
        SDL_Thread *upThread;
        upThread = SDL_CreateThread(updateThread, this);
        if(upThread == NULL){
            cout<<"Error starting upThread..."<<endl;
        }
        
        
        //draw background
        for (unsigned int i = 0; i < backgrounds.size(); i++) {
            backgrounds[i]->draw(screen, elapsed);
        }
        
        //draw drops
        for (unsigned int i = 0; i < drops.size(); i++) {
            drops[i]->draw(screen, elapsed);
        }
        
        //draw cups
        for (unsigned int i = 0; i < cups.size(); i++) {
            if (cupClickedIndex == i){
                if (!cups[i]->draw(screen, elapsed, noteClickedIndex)){
                noteClickedIndex = -1;
                    cupClickedIndex = -1;
                }
            }
            else cups[i]->draw(screen, elapsed);
        }

        
        //draw control pane
        pane->draw(screen, elapsed);
        
        
        
        //JaredTemp 3. update sprites, need to be in a while (!done) loop
        for (unsigned int i = 0; i < tempDrops.size(); i++) {
            tempDrops[i]->update(elapsed);
        }
        
        //JaredTemp 4. draw sprites, need to be in a while (!done) loop
        for (unsigned int i = 0; i < tempDrops.size(); i++) {
            tempDrops[i]->draw(screen, elapsed);
        }
        
        //JaredTemp 5. either rotate image in the .png file and keep a constant angle and figure out corresponding xvel and yvel values, OR you can look into if sdl supports rotating images.
        
        
        SDL_Flip(screen);
    }//while !done loop ends
    soundplayer->cleanup();
    SDL_Quit();
}//run ends

void RaindropGame::setDraggedObject(int x, int y){
    bool found = 0;
    while (!found) {
        for (int i = (int)cups.size()-1; i>=0;i--) {
            SDL_Rect cupRect = cups[i]->getRect();
            if( ( x > cupRect.x ) && ( x < cupRect.x + cupRect.w ) && ( y > cupRect.y ) && ( y < cupRect.y + cupRect.h ) ){
                objDragged = cups[i];
                objDragged->startDragging(x,y);
                
                cups.erase(cups.begin()+i);
                cups.push_back(objDragged);
                //  cups.insert(cups.begin(), objDragged);
                
                found = 1;
                break;
            }
        }
    }
    
}

bool RaindropGame::checkClickCup(int x, int y){
    for(int i = (int)cups.size()-1; i>=0;i--){
        SDL_Rect cupRect = cups[i]->getRect();
        if( ( x > cupRect.x ) && ( x < cupRect.x + cupRect.w ) && ( y > cupRect.y ) && ( y < cupRect.y + cupRect.h ) ){
            cupClickedIndex = i;
            return 1;
        }
    }
    return 0;
}

int RaindropGame::updateThread(void *ptr){
    RaindropGame* game = (RaindropGame*)ptr;

    //add drops if needed
    while ((int)game->drops.size() < game->numDrops && game->elapsed > game->lastDrop + game->minLatency) {
        int x = (rand()%20)*0.05*SCREENWIDTH;
        Drop *d = new Drop("Resources/drop.txt", PLAIN, x, game->gameSpeed);
        game->drops.insert(game->drops.end(), d);
        game->lastDrop = SDL_GetTicks();
    }
    
    //erase drops that are going offscreen
    for (int i = (int)game->drops.size()-1; i >= 0; i--) {
        if (game->drops[i]->isAlive() == 0) {
            Drop *d = game->drops[i];
            game->drops.erase(game->drops.begin()+i);
            delete d;
        }
    }//for all, for each, algorithms part
    
    //update background
    for (unsigned int i = 0; i < game->backgrounds.size(); i++) {
        game->backgrounds[i]->update(game->elapsed);
    }
    
    //update drops
    for (unsigned int i = 0; i < game->drops.size(); i++) {
        game->drops[i]->update(game->elapsed);
    }
    
    //update cups
    for (unsigned int i = 0; i < game->cups.size(); i++) {
        game->cups[i]->update(game->elapsed);
    }
    return 0;
}

RaindropGame::~RaindropGame(){
    //    if (upThread) SDL_KillThread(evtThread);
    
    for (unsigned int i = 0; i<backgrounds.size(); i++){
        delete backgrounds[i];
    }
    for (unsigned int i = 0; i<drops.size(); i++){
        delete drops[i];
    }
    for (unsigned int i = 0; i<cups.size(); i++){
        delete cups[i];
    }
}
