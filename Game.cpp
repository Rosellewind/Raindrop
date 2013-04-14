#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Sprite.h"
#include "Animation.h"
#include "ProtoGame.h"
#include "Game.h"


Game::Game(string fname){
    string title;
    done = false;
    ifstream in;
    
    //init sdl
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, 16, SDL_ANYFORMAT|SDL_HWSURFACE|SDL_DOUBLEBUF);

    //set title
    in.open(fname.c_str());
    getline(in, title);
    in.close();
    SDL_WM_SetCaption(title.c_str(), NULL);
}

void Game::run(){
    SDL_Event event;
    SDL_Delay(100);
    while (!done) {
        Uint32 elapsed = SDL_GetTicks();
        for (unsigned int i = 0; i < sprites.size(); i++) { //Better to use unsigned when comparing to sizes -- JaredTS
            sprites[i]->update(elapsed);
            sprites[i]->draw(screen, elapsed);
        }
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                done = true;
        }
        SDL_Flip(screen);
    }
    SDL_Quit();
}

Game::~Game(){
    SDL_FreeSurface(screen);
    screen = NULL;
    for (unsigned int i = 0; i<sprites.size(); i++) { //Better to use unsigned when comparing to sizes -- JaredTS
        delete sprites[i];
    }
}

