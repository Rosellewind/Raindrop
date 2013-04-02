/*
 g++ -o Raindrop -I /Library/Frameworks/SDL.framework/Headers -framework SDL -framework SDL_image -framework Cocoa SDLMain.m main.cpp Game.cpp Frame.cpp Animation.cpp Sprite.cpp Drop.cpp Cup.cpp ProtoGame.h RaindropGame.cpp


*/

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
    game.init("game.txt",3);//init with settings
    game.run();
    
    //won/lost screen
    return 0;
}





