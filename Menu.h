#ifndef MENU_H_
#define MENU_H_

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#endif

class Menu
{
	public:
		SDL_Surface *screen, *icon;
		TTF_Font *font;
		Mix_Music *music;
		bool running;
		int show_menu(SDL_Surface* screen, TTF_Font* font);
		int run();
};
#endif /* MENU_H_ */
