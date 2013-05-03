#ifndef MENU_H_
#define MENU_H_

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_thread.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>
#include <SDL_ttf/SDL_ttf.h>
#include <SDL/SDL_thread.h>
#include <SDL_mixer/SDL_mixer.h>

#elif __unix__
#include "SDL/SDL.h"
#include "SDL/SDL_main.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_thread.h"
#endif

#include <vector>
#include "Sprite.h"

using namespace std;
class Menu
{
public:
    int x,y,AlphaValue,FadeValue;
    SDL_Thread *thread1, *thread2;
    SDL_Surface *icon;
    TTF_Font *font;
    Mix_Music *music;
    Mix_Chunk *sound;
    SDL_Event event;
    vector<Sprite*> menuRain;
    Uint8 *Keys;
    Uint32 time;
    Sprite *droplets1;
    Sprite *droplets2;
    Sprite *droplets3;
    Sprite *droplets4;
    Sprite *droplets5;
    static const int NUMMENU = 3;
    Menu();
    ~Menu();
    int show_menu(SDL_Surface* screen, TTF_Font* font);
    SDL_Surface* LoadIMG(const char *c, Uint32 colorkey);
    void DrawIMG(SDL_Surface *img, SDL_Surface* des, int x, int y);
    void DrawDroplets(int z, int j, int num, Sprite *d);
    int run(SDL_Surface* screen);
    Menu* DESTROY();
};

#endif /* MENU_H_ */
