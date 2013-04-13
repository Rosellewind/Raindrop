#ifndef TIMER_H
#define TIMER_H

#ifdef _WIN32
#include "SDL/SDL.h"
#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>

#elif __unix__
#endif

using namespace std;

class Timer{
private:
    //The clock time when the timer started
    Uint32 startTicks;
    
    //The ticks stored when the timer was paused
    Uint32 pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
public:
    //Initializes variables
    Timer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    Uint32 get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

#endif