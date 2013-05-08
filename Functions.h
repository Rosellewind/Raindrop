/*
 * Functions.h
 *
 *  Created on: Apr 12, 2013
 *      Author: Spike
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
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

#endif /* FUNCTIONS_H_ */
