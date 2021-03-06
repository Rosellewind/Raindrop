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
#include "SDL/SDL.h"
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
    SDL_Surface *screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, 16, SDL_ANYFORMAT|SDL_HWSURFACE|SDL_DOUBLEBUF);
    
    Menu menu;
//    int i = 0;//menu.run(screen);
    int i = menu.run(screen);

    switch(i)
    {
    	case 0: 	//CASE 0 PLAY WAS SELECTED
    	{
            RaindropGame game("Resources/game.txt",3);//init with settings
            game.run(screen);
    	}
    		break;
    	case 1: 	//CASE 1 USER PRESSED QUIT
    		break;
    	case -1:	//CASE -1 USER HIT ESC OR CLOSED THE WINDOW
    		break;
    }
    
    //won/lost screen
    SDL_FreeSurface(screen);
    screen = NULL;
    SDL_Quit();
    return 0;
}