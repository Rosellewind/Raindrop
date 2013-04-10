#ifndef RAINDROPGAME_H
#define RAINDROPGAME_H

#ifdef _WIN32
#include "SDL/SDL.h"
#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#endif

#include <vector>
#include <string>
#include "Sprite.h"
#include "Drop.h"
#include "Cup.h"
#include "SoundPlayer.h"
#include "Game.h"
#include "Pane.h"

class RaindropGame: public Game{
    int numCups;
    int numDrops;
    int gameSpeed;
    int minLatency;
    vector<Drop*> drops;
    vector<Cup*> cups;
    float timestampMouseDown;
    bool isDragging;
    Sprite *objDragged;
    Sprite *background;
    Pane *pane;
    
    bool checkClickCup(int x, int y);
    void setDraggedObject(int x, int y);
public:
    RaindropGame(string fname, int cups = 3, int drops = 10, int speed = 50, int latency = 800);
    void run();
    void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
    ~RaindropGame();
    
};
#endif
