#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "SDL/SDL_thread.h"
#include "Menu.h"
#include "Sprite.h"
#include "Animation.h"
#include "Functions.h"

//Test change for repo
using namespace std;
SDL_Surface *load_image(const char *c, Uint32 colorkey = 0)
{
	SDL_Surface *tmp = IMG_Load(c);
	if(colorkey != 0) {
		SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, colorkey);
	}
	return tmp;
}
int Menu::show_menu(SDL_Surface* screen, TTF_Font* font, void *data)
{
	running = true;
	//show_background(screen, NULL); //need to thread this or make new class
	Uint32 time;
	int x, y;
	const int NUMMENU = 2; //NUMBER OF MENU ITEMS
	const char* labels[NUMMENU] = {"Play","Exit"}; //LABELS FOR THE MENU ITEMS
	SDL_Surface* menus[NUMMENU]; //SURFACES INIT FOR THE MENU ITEMS
	bool selected[NUMMENU] = {0,0}; //CHECK WHETHER WE HAVE OUR MOUSE OVER THE BUTTON
	SDL_Color color[2] = {{255,255,255},{255,255,0}}; //COLORS FOR EACH MENU ITEM {{DEFAULT COLOR},{HIGHLIGHT COLOR}}
	menus[0] = TTF_RenderText_Solid(font,labels[0],color[0]); //INIT FOR EACH NUMMENU
	menus[1] = TTF_RenderText_Solid(font,labels[1],color[0]);
	SDL_Rect pos[NUMMENU]; //POSITION OF WHERE THE BUTTONS ARE

	//POSITION OF THE RECTANGULAR BUTTONS
	pos[0].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	pos[0].y = screen->clip_rect.h/2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	pos[1].y = screen->clip_rect.h/2 + menus[0]->clip_rect.h;

	SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00)); //FILL COLOR OF THE MENU BACKGROUND
	SDL_Event event;

	while(1) {
		time = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
					running = false;
					status = -1;
					break;
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
							running = false;
							status = i;
						}
					} break;
				case SDL_KEYDOWN: //USER HITS ESC
					if(event.key.keysym.sym == SDLK_ESCAPE) {
						SDL_FreeSurface(menus[0]);
						SDL_FreeSurface(menus[1]);
						running = false;
						status = -1;
					}break;
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
	status = -111;
	return status;
}
int Menu::show_background(SDL_Surface* screen, void *data)
{
	SDL_Surface *dropSprite[6]; //Various droplet sizes
	SDL_Rect dropPos[6];
	Uint32 now, last;

	for(int i = 0; i < 6; i++)
	{
		std::string str = "Resources/images/droplet"+NTS(i)+".png";
		const char * c = str.c_str();
		dropSprite[i] = load_image(c); //DROPSPRITE CONTAINS RAINDROPS SMALL TO BIG 6-0
	}
	while(running)
	{
		dropPos[6].x = (rand()%20)*0.05*SCREENWIDTH;
		now = SDL_GetTicks(); // GRAB TIMESTAMP NOW
		last = now; //LAST DROP WAS JUST NOW
	    SDL_BlitSurface(dropSprite[6], NULL, screen, &dropPos[6]);
	    SDL_UpdateRect(screen, 0, 0, 0, 0);
	}
	return 0;
}
void Menu::clean_up()
{
    SDL_KillThread( thread1 );
    SDL_KillThread( thread2 );
    SDL_FreeSurface( screen );
    SDL_FreeSurface( icon );
    SDL_Quit();
}
int Menu::run()
{
	thread1 = NULL;
	thread2 = NULL;
	screen = SDL_SetVideoMode(SCREENWIDTH,SCREENHEIGHT,32,SDL_SWSURFACE);
	icon = load_image("Resources/images/icon.bmp"); //ICON IN THE WINDOW AND NAV BAR
	SDL_WM_SetIcon(icon, NULL); //SETTING THE ICON
	SDL_WM_SetCaption("Raindrop Game", NULL); //SETTING THE CAPTION FOR THE MENU WINDOW
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	music = Mix_LoadMUS("Resources/sounds/menu_music.ogg");
	Mix_PlayMusic(music,-1);
	font = TTF_OpenFont("Resources/fonts/Test.ttf",30);
	running = false;
	show_menu(screen,font, NULL);

	//thread2 = SDL_CreateThread( show_menu(screen,font, NULL), NULL ); //LOOP IS IN FUNCTION NOT IN RUN
	//thread1 = SDL_CreateThread( menu_background(NULL), NULL ); //LOOP IS IN FUNCTION NOT IN RUN

	SDL_WaitThread(thread1, NULL);
	SDL_WaitThread(thread2, NULL);
	if(status==1) {running = false;} //CALL FOR QUIT GAME OR QUIT MENU
	if(status==-111) {} //SOMETHING WENT WRONG
	SDL_FreeSurface(icon);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	clean_up();
	return status;
}

