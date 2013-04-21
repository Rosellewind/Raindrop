#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#ifdef _WIN32
#include "SDL/SDL.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#include "SDL/SDL.h"
#endif

#include "ProtoGame.h"
#include "Pane.h"
#include "SoundPlayer.h"
#include <vector>


using namespace std;
class LevelManager {
    vector<Note> pattern;
    int points;
    int level;
    int subLevel;
    Pane *pane;
    SoundPlayer *soundplayer;
    vector<Note> notesClicked;
    
public:
    LevelManager(int lvl, Pane *p, SoundPlayer *sp);
    void checkPattern(Note note);
    bool checkMatching(int index);
    void newPattern();
    bool isSamePattern(vector<Note> lastPattern,vector<Note> pattern);
    Note intToNote(int i);
    Note raiseNote(Note note);
    Note randomNote();
    
    vector<Note> getPattern();
};






#endif