#include <string>
#include <stdlib.h>
#include "Menu.h"
#include "Drop.h"
#include "Animation.h"
#include "Functions.h"

using namespace std;
BSprite::BSprite(int num){
    sprite = NULL;
    xPos = 0.0; xVel = 0.0;
    yPos = 0.0; yVel = 0.0;
	string filename = "Resources/images/droplet"+NTS(num)+".png";
    SDL_Surface *temp = IMG_Load(filename.c_str());
    sprite = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    if(sprite == NULL) {
        std::cout << "failed to load sprite " << filename << std::endl;
        loaded = false;
    }
}
bool BSprite::SpriteExists(){
    return loaded;
}
BSprite* BSprite::DRAW(SDL_Surface* buffer, int x, int y){
	if(!SpriteExists()) {
		std::cout << "Failed to draw, Sprite not initialized!"<< std::endl;
		return this;
	}
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	SDL_BlitSurface(sprite, NULL, buffer, &dstrect);
	return this;
}
BSprite::~BSprite(){
    DESTROY();
}
BSprite* BSprite::DESTROY(){
    if(SpriteExists()) {
        SDL_FreeSurface(sprite);
    }
    return this;
}
SDL_Surface *load_image(const char *c, Uint32 colorkey = 0){
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
int Menu::show_menu(SDL_Surface* screen, TTF_Font* font){
	BSprite DROPLET = BSprite(1);
	const int NUMMENU = 3; //NUMBER OF MENU ITEMS
	const char* labels[NUMMENU] = {"Play","Settings","Exit"}; //LABELS FOR THE MENU ITEMS
	SDL_Surface* menus[NUMMENU]; //SURFACES INIT FOR THE MENU ITEMS
	bool selected[NUMMENU] = {0,0,0}; //CHECK WHETHER WE HAVE OUR MOUSE OVER THE BUTTON
	SDL_Color color[3] = {{255,255,255},{255,255,0},{60,60,60}}; //COLORS FOR EACH MENU ITEM {{DEFAULT COLOR},{HIGHLIGHT COLOR}}
	SDL_Rect pos[NUMMENU]; //POSITION OF WHERE THE BUTTONS ARE
	Uint8 *Keys;
	Keys = SDL_GetKeyState( 0 );
	for(int i = 0; i < NUMMENU; i++) menus[i] = TTF_RenderText_Shaded(font,labels[i],color[0],color[2]);
	for(int i = 0; i < NUMMENU; i++) //SHOULD MAKE BUTTON CLASS AT SOME POINT IF TIME
	{
		if(i == 0) pos[i].y = screen->clip_rect.h/2 - menus[i]->clip_rect.h;
		else pos[i].y = pos[i-1].y + menus[i]->clip_rect.h + 5; //5 Is spacing between menu items
		pos[i].x = screen->clip_rect.w/2 - menus[i]->clip_rect.w/2;
		pos[i].w = menus[i]->clip_rect.w;
		pos[i].h = menus[i]->clip_rect.h;
	}
	SDL_Surface* tempScreen = SDL_CreateRGBSurface( SDL_SWSURFACE | SDL_SRCALPHA, SCREENWIDTH, SCREENHEIGHT, 32, 0xff000000,0x00ff0000,0x0000ff00,0x000000ff);
	SDL_Surface* tempScreen2 = SDL_DisplayFormat( tempScreen );
	SDL_FreeSurface( tempScreen );
	AlphaValue = 0;
	int FadeValue = 3;
	while(1) {
		time = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
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
								menus[i] = TTF_RenderText_Shaded(font,labels[i],color[1],color[2]);
							}
						}
						else{
							if(selected[i]) {
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Shaded(font,labels[i],color[0],color[2]);
							}
						}
					} break;
				case SDL_MOUSEBUTTONDOWN: //USER CLICKS PLAY RETURNS 0, SETTINGS 1, EXIT 3
					x = event.button.x;
					y = event.button.y;
					for(int i = 0; i < NUMMENU; i += 1) {
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
						{
							SDL_FreeSurface(menus[0]);
							SDL_FreeSurface(menus[1]);
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
						return 1;
					}
					break;
			}
		}
		SDL_FillRect( tempScreen2, 0, SDL_MapRGBA(tempScreen2->format, 60, 60, 60, 0) );
		SDL_FillRect( screen, 0, SDL_MapRGBA(tempScreen2->format, 0, 0, 0, 0) );
		if((AlphaValue + FadeValue) > 0 && (AlphaValue + FadeValue) < 255) AlphaValue = AlphaValue + FadeValue;
		for(int i = 0; i < NUMMENU; i += 1) DrawIMG( menus[i], tempScreen2, pos[i].x, pos[i].y ); //DRAW ALL BUTTONS BEFORE FADE
		DrawIMG( tempScreen2, screen, 0, 0 );
		SDL_SetAlpha( tempScreen2, SDL_SRCALPHA, AlphaValue);
		SDL_Flip(screen);
		if(1000/30 > (SDL_GetTicks()-time)) {
			SDL_Delay(1000/30 - (SDL_GetTicks()-time)); //30 FRAMES A SECOND
		}
	}
	return -111;
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
	int i = show_menu(screen,font);
	//thread2 = SDL_CreateThread( show_menu(screen,font, NULL), NULL ); //LOOP IS IN FUNCTION NOT IN RUN
	//thread1 = SDL_CreateThread( menu_background(NULL), NULL ); //LOOP IS IN FUNCTION NOT IN RUN
	//SDL_WaitThread(thread1, NULL);
	//SDL_WaitThread(thread2, NULL);
    //SDL_KillThread( thread1 );
    //SDL_KillThread( thread2 );
	TTF_CloseFont(font);
    SDL_FreeSurface( screen );
    SDL_FreeSurface( icon );
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    atexit(SDL_Quit);
	return i;
}

