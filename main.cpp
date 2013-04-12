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
#include "Menu.h"

using namespace std;

int main(int argc, char **argv){
<<<<<<< HEAD
=======
    RaindropGame game;
    Menu menu;

>>>>>>> refs/remotes/origin/Spike
    //menu screen, pick level, settings
    int i = menu.run();

    //game screen
<<<<<<< HEAD
    RaindropGame game("game.txt",3);//init with settings
    game.run();
=======
    switch(i)
    {
    	case 0: game.init("game.txt"); 	//CASE 0 PLAY WAS SELECTED
    			game.run();
    		break;
    	case 1: 						//CASE 1 USER PRESSED QUIT
    		break;
    	case -1:						//CASE -1 USER HIT ESC OR CLOSED THE WINDOW
    		break;
    }
>>>>>>> refs/remotes/origin/Spike
    
    //won/lost screen
    return 0;
}





