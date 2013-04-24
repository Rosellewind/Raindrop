#ifndef RAINDROPGAME_H
#define RAINDROPGAME_H

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>
#include <SDL/SDL_thread.h>

#elif __unix__
#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"
#endif

#include <vector>
#include <string>
#include "Sprite.h"
#include "Drop.h"
#include "Cup.h"
#include "SoundPlayer.h"
#include "Game.h"
#include "Pane.h"
#include "GameManager.h"

class RaindropGame: public Game{
    int numCups;
    int numDrops;
    int gameSpeed;
    int minLatency;
    vector<Sprite*> backgrounds;
    vector<Drop*> drops;
    vector<Cup*> cups;
    float timestampMouseDown;
    bool isDragging;
    Uint32 elapsed;
    Uint32 last;
    Uint32 lastDrop;
    //    Sprite *objDragged;
    Sprite *background;
    Pane *pane;
    Cup *objDragged;
    SoundPlayer *soundplayer;
    GameManager *gameManager;
    int noteClickedIndex;
    int cupClickedIndex;
    
    //JaredTemp 1. declare vector.
    vector<Sprite*> tempDrops;


    
    
    bool checkClickCup(int x, int y);
    void setDraggedObject(int x, int y);
    bool checkMatching(int index);
    void checkPattern(Note note);
    static int updateThread(void *ptr);
    
public:
    RaindropGame(string fname, int cups = 3, int drops = 10, int speed = 50, int latency = 800, int lvl = 1);
    void run();
    void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
    ~RaindropGame();
    
};
#endif
