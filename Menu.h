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
#endif



#include <vector>
#include "Drop.h"

class Menu
{
	public:
		int status;
		SDL_Thread *thread1, *thread2;
		SDL_Surface *screen, *icon;
		TTF_Font *font;
		Mix_Music *music;
		bool running;
		int numDrops;
		vector<Sprite*> dropSprites;
		int show_menu(SDL_Surface* screen, TTF_Font* font, void *data);
		int show_background(SDL_Surface* screen, void *data);
		void clean_up();
		int run();
};
#endif /* MENU_H_ */
