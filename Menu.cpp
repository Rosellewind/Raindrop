
#include <iostream>
#include <string>
#include "Menu.h"
#include "Sprite.h"
#include "Animation.h"

using namespace std;
SDL_Surface *load_image(const char *c, Uint32 colorkey = 0)
{
	SDL_Surface *tmp = IMG_Load(c);
	if(colorkey != 0) {
		SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, colorkey);
	}
	return tmp;
}
void DrawIMG(SDL_Surface *img, SDL_Surface* des, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_BlitSurface(img, NULL, des, &dest);
}
int Menu::show_menu(SDL_Surface* screen, TTF_Font* font)
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
	menus[0] = TTF_RenderText_Shaded(font,labels[0],color[0],{60,60,60}); //INIT FOR EACH NUMMENU
	menus[1] = TTF_RenderText_Shaded(font,labels[1],color[1],{60,60,60});
	SDL_Rect pos[NUMMENU]; //POSITION OF WHERE THE BUTTONS ARE

	Uint8 *Keys;
	Keys = SDL_GetKeyState( 0 );
	SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGBA(screen->format,0x00,0x00,0x00,0x00));
	pos[0].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	pos[0].y = screen->clip_rect.h/2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	pos[1].y = screen->clip_rect.h/2 + menus[0]->clip_rect.h;
	cout << pos[0].x << + ":" + pos[0].y << endl;
	cout << pos[0].w << + ":" + pos[0].h << endl;

	SDL_Surface* tempScreen = SDL_CreateRGBSurface( SDL_SWSURFACE | SDL_SRCALPHA, SCREENWIDTH, SCREENHEIGHT, 32, 0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
	SDL_Surface* tempScreen2 = SDL_DisplayFormat( tempScreen );
	SDL_FreeSurface( tempScreen );

	//SDL_FillRect(tempScreen2,&tempScreen2->clip_rect,SDL_MapRGB(tempScreen2->format,0x00,0x00,0x00)); //FILL COLOR OF THE MENU BACKGROUND

	int AlphaValue = 0;
	SDL_Event event;

	while(1) {
		time = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
					running = false;
					return -1;
					break;
				case SDL_MOUSEMOTION: //USER HOVERS OVER THE BUTTON
					x = event.motion.x;
					y = event.motion.y;
					for(int i = 0; i < NUMMENU; i += 1) {
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h) {
							if(!selected[i]){
								selected[i] = 1;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Shaded(font,labels[i],color[1],{0,0,0});
								cout << i << endl;
							}
						}
						else{
							if(selected[i]) {
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Shaded(font,labels[i],color[0],{0,0,0});
								cout << i << endl;
							}
						}
					} break;
				case SDL_MOUSEBUTTONDOWN: //USER CLICKS PLAY RETURNS 0, EXIT 1
					x = event.button.x;
					y = event.button.y;
					cout << x << + "::" + y << endl;
					cout << pos[0].x << + ":" + pos[0].y << endl;
					cout << pos[0].x+pos[0].w << + ":" + pos[0].y+pos[0].h << endl;
					for(int i = 0; i < NUMMENU; i += 1) {
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
						{
							cout << "clicked " + i << endl;
							SDL_FreeSurface(menus[0]);
							SDL_FreeSurface(menus[1]);
							running = false;
							if(i==0){
								Mix_PlayChannel(-1,sound,1);
								SDL_Delay(1000);
							}
							return i;
						}
					} break;
				case SDL_KEYDOWN:
					if( Keys[SDLK_ESCAPE] )
					{
						SDL_FreeSurface(menus[0]);
						SDL_FreeSurface(menus[1]);
						running = false;
						cout << "esc" << endl;
						return 1;
					}
					break;
			}
		}
		SDL_FillRect( tempScreen2, 0, SDL_MapRGBA(tempScreen2->format, 60, 60, 60, 0) );
		SDL_FillRect( screen, 0, SDL_MapRGBA(tempScreen2->format, 0, 0, 0, 0) );
		if(AlphaValue < 255){
			for(int i = 0; i < NUMMENU; i += 1) {
				DrawIMG( menus[i], tempScreen2, pos[i].x, pos[i].y );
				SDL_SetAlpha( tempScreen2, SDL_SRCALPHA, AlphaValue);
				DrawIMG( tempScreen2, screen, 0, 0 );
				AlphaValue++;
			}
		}
		else{
			for(int i = 0; i < NUMMENU; i += 1) {
				DrawIMG( menus[i], tempScreen2, pos[i].x, pos[i].y );
				DrawIMG( tempScreen2, screen, 0, 0 );
			}
		}
		SDL_Flip(tempScreen2);
		SDL_Flip(screen);
		if(1000/30 > (SDL_GetTicks()-time)) {
			SDL_Delay(1000/30 - (SDL_GetTicks()-time)); //30 FRAMES A SECOND
		}
	}
	return -111;
}
int Menu::show_background(SDL_Surface* screen)
{
	//Sprite DROP = new Sprite("Resources/images/droplet7.png");

	return 0;
}
int Menu::run()
{
	//thread1 = NULL;
	//thread2 = NULL;

	screen = SDL_SetVideoMode(SCREENWIDTH,SCREENHEIGHT,32,SDL_SWSURFACE);
	icon = load_image("Resources/images/icon.bmp"); //ICON IN THE WINDOW AND NAV BAR
	SDL_WM_SetIcon(icon, NULL); //SETTING THE ICON
	SDL_WM_SetCaption("Raindrop Game", NULL); //SETTING THE CAPTION FOR THE MENU WINDOW
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO);
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	music = Mix_LoadMUS("Resources/sounds/menu_music.ogg");
	sound = Mix_LoadWAV("Resources/sounds/confirm.ogg");
	Mix_PlayMusic(music,-1);
	font = TTF_OpenFont("Resources/fonts/Test.ttf",30);
	running = false;
	int i = show_menu(screen,font);

	//thread2 = SDL_CreateThread( show_menu(screen,font, NULL), NULL ); //LOOP IS IN FUNCTION NOT IN RUN
	//thread1 = SDL_CreateThread( menu_background(NULL), NULL ); //LOOP IS IN FUNCTION NOT IN RUN
	//SDL_WaitThread(thread1, NULL);
	//SDL_WaitThread(thread2, NULL);

	if(i==1) {running = false;} //CALL FOR QUIT GAME OR QUIT MENU
	if(i==-111) {} //SOMETHING WENT WRONG

    //SDL_KillThread( thread1 );
    //SDL_KillThread( thread2 );
	TTF_CloseFont(font);
    SDL_FreeSurface( screen );
    SDL_FreeSurface( icon );
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
	return i;
}

