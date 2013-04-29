#include "Functions.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

GRN::GRN()
{
	max = 10.0;
	min = 0.0;
	result = 0.0;
	time2 = SDL_GetTicks();
}
double GRN::GET(double min, double max)
{
	seconds = time(NULL);
	time2 = SDL_GetTicks();
	srand(time2 % SDL_GetTicks() / seconds);
	result = (double)(max * (rand() / (RAND_MAX + min)));
	return result;
}
