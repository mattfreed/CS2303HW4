/*
 * Clock.h
 *
 *  Created on: Feb 14, 2018
 *      Author: jbpinzer
 */

#ifndef CLOCK_H_
#define CLOCK_H_

class Clock {
	public:
		Clock();
		virtual ~Clock();
		float addTime(float t);
		float setTime(float t);
		float getTime();
	private:
		float time;
};

#endif /* CLOCK_H_ */
