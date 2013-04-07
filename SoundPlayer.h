#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_mixer/SDL_mixer.h>

#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "ProtoGame.h"
using namespace std;

class SoundPlayer{
	Mix_Music *music;
	vector<Mix_Chunk*> sounds;
public:
	SoundPlayer();
	void init(int freq, int channels, int chunkSize);
	void load_sounds(string fname);
	void cleanup();
	void playMusic();
	void playSound();
	void playSound(Note n);
	void togglePauseMusic();	
};

#endif