#ifndef PANE_H
#define PANE_H

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>

#elif __unix__
#endif

#include <vector>
#include "Text.h"
#include "ProtoGame.h"
#include "Animation.h"

using namespace std;
class Pane{
    SDL_Rect rect;
    vector<Text*> staticText;
    Text *pointsText;
    Text *levelText;
    Frame *pool;
    vector<Animation*> pools;
    int poolIndex;
    SDL_Rect poolRect;
    
public:
    Pane();
    void draw(SDL_Surface *screen, Uint32 elapsed);
    void updatePoints(int points);
    void updateLevel(int level);
    void flashColor(Note note);
    ~Pane();
};

#endif
