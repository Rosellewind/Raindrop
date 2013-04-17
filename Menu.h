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
#include "Functions.h"

class Menu
{
	public:
		Uint32 time;
		int x,y,AlphaValue;
		SDL_Thread *thread1, *thread2;
		SDL_Surface *screen, *icon;
		TTF_Font *font;
		Mix_Music *music;
		Mix_Chunk *sound;
		SDL_Event event;
		int show_menu(SDL_Surface* screen, TTF_Font* font);
		int show_background(SDL_Surface* screen);
		void DrawIMG(SDL_Surface *img, SDL_Surface* des, int x, int y);
		int run();

};
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
};
#endif /* MENU_H_ */
