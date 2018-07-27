#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <cstdlib>

using namespace std;

class Event {
	public:
		Event(float startTime);
		Event();
		~Event();

		int setAction(int action);
		int getAction();
		float getLength(float endTime);
		float getStartTime();
		float setStartTime(float time);
		float setAverageServiceTime(float averageServiceTime);
		float getAverageServiceTime();

		int setLine(int line);
		int getLine();

	protected:
		float averageServiceTime;
		float startTime;
		int action; // Default action is 1, means the customer is in line or the teller has no customer
		int line;
};

#endif
