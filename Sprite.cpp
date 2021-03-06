#include <iostream>
#include <fstream>
#include "ProtoGame.h"
#include "Sprite.h"
#include "Animation.h"


Sprite::Sprite(int column, string fname, bool isLoop,
               float newXPos, float newYPos,
               float newXVel, float newYVel,
               float newXAcc, float newYAcc){
    animation = new Animation(fname.c_str(),column, isLoop);
    xPos = newXPos;
    yPos = newYPos;
    xVel = newXVel;
    yVel = newYVel;
    xAcc = newXAcc;
    yAcc = newYAcc;
    last = SDL_GetTicks();
    offsetX = offsetY = 0;
    isDragging = false; //Initialize -- JaredTS
}

void Sprite::update(Uint32 elapsed){
    Uint32 next = SDL_GetTicks();
    float deltaT = (float)(next-last);
    last = next;
    if (deltaT > 0.0){
        xVel += xAcc/deltaT;
        yVel += yAcc/deltaT;
        xPos += xVel/deltaT;
        yPos += yVel/deltaT;
        if ((int)xPos > SCREENWIDTH) {
        	yPos = rand() % SCREENHEIGHT;
        	xPos = -40;
        }
        if ((int)yPos > SCREENHEIGHT) {
        	xPos = rand() % SCREENWIDTH;
        	yPos= -40;
        }
    }
}

void Sprite::draw(SDL_Surface *screen, Uint32 elapsed){
    animation->draw(screen, xPos, yPos, elapsed);
}

SDL_Rect Sprite::getRect(){
    return animation->getRect();
}

bool Sprite::isAlive(){
    return 1;
}

void Sprite::dragTo(int x, int y){

    xPos = (float)x - offsetX;
	yPos = (float)y - offsetY;
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

void Sprite::startDragging(int x, int y){
    SDL_Rect rect = getRect();
    isDragging = true;
    offsetX = x - rect.x;
    offsetY = y - rect.y;
}

void Sprite::stopDragging(){
    isDragging = false;
}

Sprite::~Sprite(){
    cout<<"...cup deconstructor..."<<endl;
    if (animation)
        delete animation;
}

