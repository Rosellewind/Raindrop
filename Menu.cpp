#include <string>
#include <stdlib.h>
#include "Menu.h"
#include "Drop.h"
#include "Animation.h"
#include "Functions.h"

using namespace std;

Menu::Menu()
{
	SDL_Init(SDL_INIT_VIDEO);
	icon = LoadIMG("Resources/images/droplet1.png",0);
	logo = LoadIMG("Resources/images/RainDropLogo.png",0);
	background = LoadIMG("Resources/images/CloudBackground.png",0);
	SDL_WM_SetIcon(icon, NULL); //SETTING THE ICON
	SDL_WM_SetCaption("Raindrop Game", NULL); //SETTING THE CAPTION FOR THE MENU WINDOW
	thread1 = NULL;
	thread2 = NULL;
	x = 0;
	y = 0;
	AlphaValue = 0;
	Keys = SDL_GetKeyState( 0 );
	TTF_Init();
	font = TTF_OpenFont("Resources/fonts/Arial.ttf",30);
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	music = Mix_LoadMUS("Resources/sounds/menu_music.ogg");
	sound = Mix_LoadWAV("Resources/sounds/confirm.ogg");
}
Menu::~Menu(){
    DESTROY();
}
Menu* Menu::DESTROY()
{
	TTF_CloseFont( font );
    SDL_FreeSurface( icon );
    Mix_FreeMusic( music );
    Mix_CloseAudio();
    TTF_Quit();
    return this;
}
SDL_Surface* Menu::LoadIMG(const char *c, Uint32 colorkey){
	SDL_Surface *tmp = IMG_Load(c);
	if(colorkey != 0) {
		SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, colorkey);
	}
	return tmp;
}
void Menu::DrawIMG(SDL_Surface *img, SDL_Surface* des, int x, int y){
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface(img, NULL, des, &dest);
}
void Menu::DrawObjects(int z, int j, int num, Sprite *d)
{
	for (int i = 0; i<num; i++)
	{
		int diff = (rand() % z) - z/3;
		float xx = (rand() % SCREENWIDTH) - 40;
		float yy = (rand() % SCREENHEIGHT) - 40;
		d = new Sprite(j,"Resources/menuDrops.txt", true, xx, yy, z+diff, z);
		menuRain.push_back(d);
	}
}
void Menu::UpdateScreen(SDL_Surface* screen, int FadeValue, int r, int g, int b, int a)
{
	SDL_FillRect( tempScreen2, 0, SDL_MapRGBA(tempScreen2->format, 60, 60, 60, 0) );
	SDL_FillRect( screen, 0, SDL_MapRGBA(tempScreen2->format, 0, 0, 0, 0) );
	if((AlphaValue + FadeValue) > 0 && (AlphaValue + FadeValue) < 255) AlphaValue = AlphaValue + FadeValue;
	DrawIMG( tempScreen2, screen, 0, 0 );
	DrawIMG( background2, screen, 0, 0 );
	SDL_SetAlpha( tempScreen2, SDL_SRCALPHA, AlphaValue);
	for (unsigned int i = 0; i < menuRain.size(); i++) menuRain[i]->update(time);
	for (unsigned int i = 0; i < menuRain.size(); i++) menuRain[i]->draw(screen,time);
	for (int i = 0; i < NUMMENU; i += 1) DrawIMG( menus[i], screen, pos[i].x, pos[i].y ); //DRAW ALL BUTTONS BEFORE FADE
	DrawIMG( logo, screen, (SCREENWIDTH/2)-(logo->clip_rect.w/2)+10, 100 );
	SDL_Flip(screen);
	if(1000/200 > (SDL_GetTicks()-time)) SDL_Delay(1000/200 - (SDL_GetTicks()-time));
}
int Menu::show_menu(SDL_Surface* screen, TTF_Font* font){
	Mix_PlayMusic(music,-1);
	const char* labels[NUMMENU] = {"Play","Settings","Exit"}; //LABELS FOR THE MENU ITEMS
	bool selected[NUMMENU] = {0,0,0}; //CHECK WHETHER WE HAVE OUR MOUSE OVER THE BUTTON
	SDL_Color color[3] = {{255,255,255},{255,255,0},{60,60,60}}; //COLORS FOR EACH MENU ITEM {{DEFAULT COLOR},{HIGHLIGHT COLOR}}
	for(int i = 0; i < NUMMENU; i++) menus[i] = TTF_RenderText_Blended(font,labels[i],color[0]);
	for(int i = 0; i < NUMMENU; i++) //SHOULD MAKE BUTTON CLASS AT SOME POINT IF TIME
	{
		if(i == 0) pos[i].y = screen->clip_rect.h/2 - menus[i]->clip_rect.h;
		else pos[i].y = pos[i-1].y + menus[i]->clip_rect.h + 5; //5 Is spacing between menu items
		pos[i].x = screen->clip_rect.w/2 - menus[i]->clip_rect.w/2;
		pos[i].w = menus[i]->clip_rect.w;
		pos[i].h = menus[i]->clip_rect.h;
	}
	DrawObjects(10,0,4,droplets1);
	DrawObjects(6,1,8,droplets2);
	DrawObjects(8,2,12,droplets3);
	DrawObjects(4,3,16,droplets4);
	DrawObjects(2,4,20,droplets5);
	tempScreen = SDL_CreateRGBSurface( SDL_SWSURFACE | SDL_SRCALPHA, SCREENWIDTH, SCREENHEIGHT, 32, 0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
	tempScreen2 = SDL_DisplayFormat( tempScreen );
	background2 = SDL_DisplayFormatAlpha( background );
	SDL_FreeSurface( tempScreen );
	SDL_FreeSurface( background );
	while(1) {
		time = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					for(int i = 0; i < NUMMENU; i += 1) SDL_FreeSurface(menus[i]);
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
								menus[i] = TTF_RenderText_Blended(font,labels[i],color[1]);
							}
						}
						else{
							if(selected[i]) {
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Blended(font,labels[i],color[0]);
							}
						}
					} break;
				case SDL_MOUSEBUTTONDOWN: //USER CLICKS PLAY RETURNS 0, SETTINGS 1, EXIT 2
					x = event.button.x;
					y = event.button.y;
					for(int i = 0; i < NUMMENU; i += 1) {
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h){
							if(i==0){
								Mix_PlayChannel(-1,sound,0);
								while(AlphaValue > 1){
									UpdateScreen(screen,-1,0,0,0,0);
								}
							}
							for(int i = 0; i < NUMMENU; i += 1) SDL_FreeSurface(menus[i]);
							return i;
						}
					} break;
				case SDL_KEYDOWN:
					if( Keys[SDLK_ESCAPE] ) {
						for(int i = 0; i < NUMMENU; i += 1) SDL_FreeSurface(menus[i]);
						return 1;
					}break;
			}
		}	UpdateScreen(screen,1,0,0,0,0);
	}
	return -111;
}
int Menu::run(SDL_Surface* screen)
{
	int i = show_menu(screen,font);
	//thread2 = SDL_CreateThread( show_menu(screen,font, NULL), NULL ); //LOOP IS IN FUNCTION NOT IN RUN
	//thread1 = SDL_CreateThread( menu_background(NULL), NULL ); //LOOP IS IN FUNCTION NOT IN RUN
	//SDL_WaitThread(thread1, NULL);
	//SDL_WaitThread(thread2, NULL);
    //SDL_KillThread( thread1 );
    //SDL_KillThread( thread2 );
	TTF_CloseFont(font);
	//SDL_FreeSurface( screen );
    SDL_FreeSurface( icon );
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
	//SDL_Quit();
	//atexit(SDL_Quit);
	return i;
}