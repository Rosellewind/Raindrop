#ifndef PROTOGAME_H
#define PROTOGAME_H
#include <string>

const int SCREENWIDTH=800;
const int SCREENHEIGHT=600;
const int GAMESCREENHEIGHT=480;
const int FRAMES_PER_SECOND = 10;
const int MIN_FRAMETIME_MSECS = 100;

enum Type{PLAIN, COLOR, SLOW, DRAIN};
enum Note{LC, D, E, F, G, A, B, HC};

const std::string Note_String[] = {"lc", "d", "e", "f", "g", "a", "b", "hc"};


#endif

/*
class ProtoGame{
public:
    static int screenwidth;
};
int ProtoGame::screenwidth = 640;   //this part should be in .cpp file
*/