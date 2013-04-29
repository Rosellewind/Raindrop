/*
 * Functions.h
 *
 *  Created on: Apr 12, 2013
 *      Author: Spike
 */
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#ifdef _WIN32
#include "SDL/SDL.h"

#elif __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL_image/SDL_image.h>

#elif __unix__
#include "SDL/SDL.h"
#endif

#include <string>
#include <sstream>
#include <iostream>
using namespace std;

template <typename T>
T STN ( const string &Text )
{
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}

template <typename U>
string NTS ( U Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

class GRN
{
	public:
		time_t seconds;
		double min;
		double max;
		double result;
		Uint32 time2;
		GRN();
		double GET(double min, double max);
};

#endif /* FUNCTIONS_H_ */
