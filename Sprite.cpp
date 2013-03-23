#include <iostream>
#include <fstream>
#include "ProtoGame.h"
#include "Sprite.h"
#include "Animation.h"


void Sprite::init(string fname,
                  float newXPos, float newYPos,
                  float newXVel, float newYVel,
                  float newXAcc, float newYAcc){
    animation = new Animation;
    animation->init(fname.c_str());
    xPos = newXPos;
    yPos = newYPos;
    xVel = newXVel;
    yVel = newYVel;
    xAcc = newXAcc;
    yAcc = newYAcc;
    last = SDL_GetTicks();
    offsetX = offsetY = 0;
}

void Sprite::update(long elapsed){
    long next = SDL_GetTicks();
    float deltaT = (float)(next-last);
    last = next;
    if (deltaT > 0.0){
        
        xVel += xAcc/deltaT;
        yVel += yAcc/deltaT;
        xPos += xVel/deltaT;
        yPos += yVel/deltaT;
        if ((int)xPos > SCREENWIDTH) xVel = -xVel;
        if ((int)yPos > GAMESCREENHEIGHT) yVel = -yVel;
        if ((int)xPos < 0) xVel = -xVel;
        if ((int)yPos < 0) yVel = -yVel;
    }
}

void Sprite::draw(SDL_Surface *screen, long elapsed ){
    animation->draw(screen, xPos, yPos, elapsed);
}

SDL_Rect Sprite::getRect(){
    return animation->getRect();
}

bool Sprite::isAlive(){
    return 1;
}

void Sprite::startDragging(int x, int y){
    SDL_Rect rect = getRect();
    isDragging = true;
    offsetX = x - rect.x;
    offsetY = y - rect.y;
}

void Sprite::dragTo(int x, int y){
    xPos = (float)x - offsetX;
	yPos = (float)y - offsetY;
}

void Sprite::stopDragging(){
    isDragging = false;
}

bool Sprite::checkCollisionByCenter(SDL_Rect rect1){
    SDL_Rect rect2 = getRect();
    int centerOfRect1 = rect1.x + .5 * rect1.w;
    int leftOfRect2 = rect2.x;
    int rightOfRect2 = rect2.x + rect2.w;
    if (centerOfRect1 > leftOfRect2 && centerOfRect1 < rightOfRect2){
        return 1;
    }
    else return 0;
}


