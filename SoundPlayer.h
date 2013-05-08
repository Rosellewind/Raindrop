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
	vector<Mix_Chunk*> sounds[3]; 
	bool done;
	int delay, pauseDelay; // in ms
	Pane *pane;
	SDL_Thread *thread;
	
public:
	int sequenceCounter;
	vector<Note> notes;
	bool pausedSequence, firstClick;
	Uint32 initialTime;
	static const int SEQUENCE_CHANNEL = 2;
	static const int CLICK_CHANNEL =1;
	
	SoundPlayer(Pane *newpane);
	void init(int freq, int channels, int chunkSize);
	void load_sounds(string fname);
	void playMusic();
	void setMusicVolume(int newVolume);
	void setSoundVolume(int newVolume, int channel);                    
	void playGlassSound(Note n);
	void playSound(Note n, int channel = SEQUENCE_CHANNEL);
	void togglePauseMusic();	
	void playNoteSequence(vector<Note> notes, int newDelay = 2000);
	void startNewSequence(vector<Note> newNotes, int newDelay = 2000);
	static int sequenceThread(void *notes);
	void setGlassVolume(int newvol);
	void setSequenceVolume(int newvol);
	void cleanup();
	void stopNoteSequence();
	void pauseNoteSequence(int delay);
    ~SoundPlayer();
};

#endif