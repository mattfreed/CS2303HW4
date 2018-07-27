/*
 * Clock.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: jbpinzer
 */

#include "Clock.h"
/** Constructor for class clock
 *
 */
Clock::Clock() {
	this->time = 0;

}

Clock::~Clock() {
	// TODO Auto-generated destructor stub
}

/** Adds time to the clock
 * @param t is the current time initialized
 * @return returns the time
 */
float Clock::addTime(float t) {
	time += t;
	return time;
}
/** sets time to the clock
 * @param t is the current time initialized
 * @return returns the time
 */
float Clock::setTime(float t) {
	time = t;
	return time;
}
/** Getter for time
 * @return returns the time
 */
float Clock::getTime() {
	return time;
}
