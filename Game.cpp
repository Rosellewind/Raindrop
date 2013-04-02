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
    Sprite *background;
    Sprite *pane;
    ifstream in;
    
    //init sdl
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, 16, SDL_ANYFORMAT|SDL_HWSURFACE|SDL_DOUBLEBUF);

    //set title
    in.open(fname.c_str());
    getline(in, title);
    in.close();
    SDL_WM_SetCaption(title.c_str(), NULL);
    
    //set background
    background = new Sprite("background.txt");
    sprites.insert(sprites.begin(), background);
    
    //set pane
    
    pane = new Sprite("pane.txt", 0, GAMESCREENHEIGHT);
    sprites.insert(sprites.begin(), pane);
}

void Game::run(){
    SDL_Event event;
    SDL_Delay(100);
    while (!done) {
        long elapsed = SDL_GetTicks();
        for (int i = 0; i < sprites.size(); i++) {
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
    for (int i = 0; i<sprites.size(); i++) {
        delete sprites[i];
    }
}

