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
    RaindropGame game;
    Menu menu;

    //menu screen, pick level, settings
    int i = menu.run();

    //game screen
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
    
    //won/lost screen
    return 0;
}





