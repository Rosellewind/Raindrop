#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#ifdef _WIN32
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_thread.h"

//untested
#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL/SDL_thread.h>
#include <SDL_mixer/SDL_mixer.h>

#elif __unix__
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_thread.h"
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Pane.h"
#include "ProtoGame.h"

using namespace std;

class SoundPlayer{
	Mix_Music *music;
	vector<Mix_Chunk*> sounds;
	bool done;
	int delay; // in ms
	Pane *pane;
	SDL_Thread *thread;
	
public:
	int sequenceCounter;
	vector<Note> notes;
	
	SoundPlayer(Pane *newpane);
	void init(int freq, int channels, int chunkSize);
	void load_sounds(string fname);
	void playMusic();
	void setMusicVolume(int newVolume);
	void playSound();
	void playSound(Note n, int channel = 2);
	void togglePauseMusic();
	void playNoteSequence(vector<Note> notes, int newDelay = 2000);
	void startNewSequence(vector<Note> newNotes, int newDelay = 2000);
	static int sequenceThread(void *notes);
	void cleanup();
	void stopNoteSequence();
    ~SoundPlayer();
};

#endif