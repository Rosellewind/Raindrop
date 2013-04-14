#include <iostream>
#include <fstream>
#include "Animation.h"
#include "ProtoGame.h"
#include "RaindropGame.h"

using namespace std;

RaindropGame::RaindropGame(string fname, int cups, int drops, int speed, int latency):Game(fname){
    gameSpeed = speed;
    numCups = cups;
    numDrops = drops;
    minLatency = latency;
    isDragging = false;
    timestampMouseDown = 0;
    objDragged = NULL;
    level = 1;
    points = 0;
    
    //set background
    background = new Sprite("Resources/background.txt");
    backgrounds.insert(backgrounds.begin(), background);
    
    //set pane
    pane = new Pane();

     //setup sound
    soundplayer = new SoundPlayer();
    soundplayer->init(44100, 2, 4096);
    soundplayer->load_sounds("Resources/audio.txt");
}

void RaindropGame::run(){
    SDL_Event event;
    last = SDL_GetTicks();
    lastDrop = last;
    SDL_Delay(100);
    
    //add cups
    cups = Cup::initCups(numCups, screen);
    
    //play sound
    soundplayer->setMusicVolume(12);
    soundplayer->playMusic();

    //play sound pattern
    pattern = {E,E};
    soundplayer->playNoteSequence(pattern);
    
    //run loop
    while (!done) {
        elapsed = SDL_GetTicks();
        if(1000/100 > (elapsed-last))
			SDL_Delay(1000/100 - (elapsed-last)); //RESTRICT PLAYBACK TO 30 FRAMES A SECOND
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
                            soundplayer->playSound(objDragged->note);
                            pane->flashColor(objDragged->note);
                            checkPattern(objDragged->note);
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
        for (int i = 0; i < backgrounds.size(); i++) {
            backgrounds[i]->draw(screen, elapsed);
        }
        
        //draw drops
        for (int i = 0; i < drops.size(); i++) {
            drops[i]->draw(screen, elapsed);
        }
        
        //draw cups
        for (int i = 0; i < cups.size(); i++) {
            cups[i]->draw(screen, elapsed);
        }
        
        //draw control pane
        pane->draw(screen, elapsed);
        
        SDL_Flip(screen);
    }//while !done loop ends
    soundplayer->cleanup();
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

//0110101 LC,D,D,LC,D,LC,D
//011011
bool RaindropGame::checkMatching(int index){
    if (index == notesClicked.size() && index == pattern.size()){
        notesClicked.clear();
        return true;
    }
    if (index < notesClicked.size() && index < pattern.size()){
        if (notesClicked[index] == pattern[index]) 
            return (checkMatching(index+1));
        else {
            notesClicked.erase(notesClicked.begin());
            if (notesClicked.size()==0) 
                return false;
            else return checkMatching(0);
        }
    }
    else
        return false;
}

void RaindropGame::checkPattern(Note note){
    notesClicked.push_back(objDragged->note);
    
    //log  the pattern and notesClicked
    for (int i = 0; i < pattern.size(); i++)
        cout<<pattern[i];
    cout<<endl;
    for (int i = 0; i < notesClicked.size(); i++)
        cout<<notesClicked[i];
    cout<<endl;
    
    bool match = checkMatching(0);
    cout<<match<<endl;

    if (match) {//temp game logic
        cout<<"match"<<endl;
        points += 5;
        pane->updatePoints(points);
        if (points >= 20){
            pane->updateLevel(2);
            pattern = {HC, LC, HC};
        }
        if (points >= 30) {
            pane->updateLevel(3);
            pattern = {D, E, F};
        }
    }
    else cout<<"nope"<<endl;
}

int RaindropGame::updateThread(void *ptr){
    RaindropGame* game = (RaindropGame*)ptr;
    
    //add drops if needed
    while (game->drops.size() < game->numDrops && game->elapsed > game->lastDrop + game->minLatency) {
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
    for (int i = 0; i < game->backgrounds.size(); i++) {
        game->backgrounds[i]->update(game->elapsed);
    }
    
    //update drops
    for (int i = 0; i < game->drops.size(); i++) {
        game->drops[i]->update(game->elapsed);
    }
    
    //update cups
    for (int i = 0; i < game->cups.size(); i++) {
        game->cups[i]->update(game->elapsed);
    }
    return 0;
}

RaindropGame::~RaindropGame(){
//    if (upThread) SDL_KillThread(evtThread);

    for (int i = 0; i<drops.size(); i++){
        delete drops[i];
    }
    for (int i = 0; i<cups.size(); i++){
        delete cups[i];
    }
}
