#ifndef SPRITE_H
#define SPRITE_H

#ifdef _WIN32
#include "SDL/SDL.h"
#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#endif

#include "Animation.h"
using namespace std;

class Sprite{
protected:
    Animation *animation;
    float xPos, yPos, xVel, yVel, xAcc, yAcc;
    Uint32 last;
    bool isDragging;
    int offsetX, offsetY;
public:
    Sprite(string fname,
           float newXPos = 0.0, float newYPos = 0.0,
           float newXVel = 0.0, float newYVel = 0.0,
           float newXAcc = 0.0, float newYAcc = 0.0);
    virtual void update(Uint32 elapsed);
    virtual void draw(SDL_Surface *screen, Uint32 elapsed );
    virtual SDL_Rect getRect();
    virtual bool isAlive();
    virtual void dragTo(int x, int y);
    
    bool checkCollisionByCenter(SDL_Rect rect1);
    void startDragging(int x, int y);
    void stopDragging();
    ~Sprite();
};

#endif
