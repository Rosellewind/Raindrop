#ifdef _WIN32
#include "SDL/SDL.h"
#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#endif

#include <iostream>
#include "Animation.h"
#include "Sprite.h"
#include <vector>
#include "ProtoGame.h"
#include "RaindropGame.h"

using namespace std;

int main(int argc, char **argv){
    RaindropGame game;
    
    //menu screen, pick level, settings
    
    //game screen
    game.init("game.txt");//init with settings
    game.run();
    
    //won/lost screen
    return 0;
}





