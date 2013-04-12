#include <iostream>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "Menu.h"

SDL_Surface *load_image(const char *c, Uint32 colorkey = 0) {
	SDL_Surface *tmp = SDL_LoadBMP(c);
	if(colorkey != 0) {
		SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, colorkey);
	}
	return tmp;
}
int Menu::show_menu(SDL_Surface* screen, TTF_Font* font) {
	Uint32 time;
	int x, y;
	const int NUMMENU = 2; //NUMBER OF MENU ITEMS
	const char* labels[NUMMENU] = {"Play","Exit"}; //LABELS FOR THE MENU ITEMS
	SDL_Surface* menus[NUMMENU]; //SURFACES INIT FOR THE MENU ITEMS
	bool selected[NUMMENU] = {0,0}; //MENU ITEMS SELECTED
	SDL_Color color[2] = {{255,255,255},{255,0,0}}; //COLORS FOR EACH MENU ITEM {{DEFAULT COLOR},{HIGHLIGHT COLOR}}
	menus[0] = TTF_RenderText_Solid(font,labels[0],color[0]); //INIT FOR EACH NUMMENU
	menus[1] = TTF_RenderText_Solid(font,labels[1],color[0]);
	SDL_Rect pos[NUMMENU]; //POSITION OF WHERE THE BUTTONS ARE

	//POSITION OF THE RECTANGULAR BUTTONS
	pos[0].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	pos[0].y = screen->clip_rect.h/2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	pos[1].y = screen->clip_rect.h/2 + menus[0]->clip_rect.h;

	SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x33,0x33,0x00)); //FILL COLOR OF THE MENU BACKGROUND

	SDL_Event event;
	while(1) {
		time = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
					return -1;
				case SDL_MOUSEMOTION: //USER HOVERS OVER THE BUTTON
					x = event.motion.x;
					y = event.motion.y;
					for(int i = 0; i < NUMMENU; i += 1) {
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h) {
							if(!selected[i]){
								selected[i] = 1;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
							}
						}
						else{
							if(selected[i]) {
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
							}
						}
					} break;
				case SDL_MOUSEBUTTONDOWN: //USER CLICKS MENU BUTTON
					x = event.button.x;
					y = event.button.y;
					for(int i = 0; i < NUMMENU; i += 1) {
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h) {
							SDL_FreeSurface(menus[0]);
							SDL_FreeSurface(menus[1]);
							return i;
						}
					} break;
				case SDL_KEYDOWN: //USER HITS ESC
					if(event.key.keysym.sym == SDLK_ESCAPE) {
						SDL_FreeSurface(menus[0]);
						SDL_FreeSurface(menus[1]);
						return -1;
					}
					break;
			}
		}
		for(int i = 0; i < NUMMENU; i += 1) {
			SDL_BlitSurface(menus[i],NULL,screen,&pos[i]);
		}
		SDL_Flip(screen);
		if(1000/30 > (SDL_GetTicks()-time)) {
			SDL_Delay(1000/30 - (SDL_GetTicks()-time)); //RESTRICT PLAYBACK TO 30 FRAMES A SECOND
		}
	}
	return -111;
}
int Menu::run()
{
	const int width = 640;
	const int height = 480;
	screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
	icon = load_image("logo.bmp");
	SDL_WM_SetIcon(icon, NULL);
	SDL_WM_SetCaption("Raindrop", NULL);
	TTF_Init();
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	music = Mix_LoadMUS("resources/sounds/menu_music.ogg");
	Mix_PlayMusic(music,-1);
	font = TTF_OpenFont("resources/fonts/Test.ttf",30);

	running = true;
	int i = show_menu(screen, font);
	if(i==1) {running = false;} //CALL FOR QUIT GAME OR QUIT MENU
	if(i==-111) {} //SOMETHING WENT WRONG
	SDL_FreeSurface(icon);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
	return i;
}

