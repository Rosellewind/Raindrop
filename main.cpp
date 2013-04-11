/*
 on mac:
 g++ -o Raindrop -I /Library/Frameworks/SDL.framework/Headers -framework SDL -framework SDL_image -framework Cocoa SDLMain.m main.cpp Game.cpp Frame.cpp Animation.cpp Sprite.cpp Drop.cpp Cup.cpp ProtoGame.h RaindropGame.cpp Pane.cpp Text.cpp
*/

#ifdef _WIN32
#include "SDL/SDL.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
 
#elif __unix__
#endif

#include <iostream>
#include "Animation.h"
#include "Sprite.h"
#include <vector>
#include "ProtoGame.h"
#include "RaindropGame.h"
#include "Menu.h"

using namespace std;

int main(int argc, char **argv){
    //menu screen, pick level, settings
    int i = menu.run();

    //game screen
    RaindropGame game("game.txt",2);//init with settings
    game.run();
    
    //won/lost screen
    return 0;
}





