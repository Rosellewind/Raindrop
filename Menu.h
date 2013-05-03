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
		int x,y,AlphaValue;
		SDL_Thread *thread1, *thread2;
		SDL_Surface *icon, *logo, *background, *tempScreen, *tempScreen2, *background2;
		TTF_Font *font;
		Mix_Music *music;
		Mix_Chunk *sound;
		SDL_Event event;
		vector<Sprite*> menuRain;
		vector<Sprite*> menuMist;
		Uint8 *Keys;
		Uint32 time;
		Sprite *droplets1;
		Sprite *droplets2;
		Sprite *droplets3;
		Sprite *droplets4;
		Sprite *droplets5;
		static const int NUMMENU = 3;
		SDL_Rect pos[NUMMENU];
		SDL_Surface * menus[NUMMENU];
		Menu();
		~Menu();
		int show_menu(SDL_Surface* screen, TTF_Font* font);
		SDL_Surface* LoadIMG(const char *c, Uint32 colorkey);
		void DrawIMG(SDL_Surface *img, SDL_Surface* des, int x, int y);
		void DrawObjects(int z, int j, int num, Sprite *d);
		void UpdateScreen(SDL_Surface* screen, int FADE, int r, int g, int b, int a);
		int run(SDL_Surface* screen);
		Menu* DESTROY();
};
/*
class BSprite
{
	public:
		BSprite();
		BSprite(int num);
		BSprite* DRAW(SDL_Surface* buffer, int x, int y);
		virtual ~BSprite();
		bool SpriteExists();
		BSprite* DESTROY();
	private:
		bool loaded;
		int xVel,yVel,xPos,yPos;
		SDL_Surface* sprite;
		void DrawIMG(SDL_Surface *img, SDL_Surface* des, int x, int y);
		int run();

};
*/
#endif /* MENU_H_ */
