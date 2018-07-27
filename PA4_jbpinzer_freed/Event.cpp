#include "Event.h"

/** Constructs an Event.
 * @param startTime the time the event starts at.
 */
Event::Event(float startTime) {
	this->startTime = startTime; //set the start time
	this->action = 1;//default action is 1
	this->line = 0;//default line is 0
	this->averageServiceTime = 0;//default average service time is 0
}

/** Constructs an event with no parameters
 */
Event::Event() {
	this->startTime = 0;//default start time is 0
	this->action = 1;//default action is 1
	this->line = 0;//default line is 0
	this->averageServiceTime = 0;//default average service time is 0
}

/** Destructs the Event class
 */
Event::~Event() {
	//Destructor
}


/** Sets the event action
 * @param action takes in the action code of the event
 * @return the action code
 */
int Event::setAction(int action) {
	this->action = action;
	return action;
}
/** Returns the action code
 * @return the action code
 */
int Event::getAction() {
	return action;
}
/** Gets the total length of the event
 * @param endTime takes in when the event ends
 * @return the end time - start time
 */
float Event::getLength(float endTime) {
	return endTime - startTime;//total time the event occurred
}

/** Gets the start time for the event
 * @return the start time
 */
float Event::getStartTime() {
	return startTime;
}

/** Sets the start time of the event
 *	@param time the start time
 *	@return the time the event starts
 */
float Event::setStartTime(float time) {
	startTime = time;
	return startTime;
}

/** Sets the line number
 * @param line is the line this event associates with
 * @return the line number
 */
int Event::setLine(int line){
	this->line = line;
	return line;
}

/** Gets the line of this event
 * @return the line number
 */
int Event::getLine() {
	return line;
}

/** Sets average service time
 * @param averageServiceTime the average service time requested
 * @return the average service time
 */
float Event::setAverageServiceTime(float averageServiceTime) {
	this->averageServiceTime = averageServiceTime;
	return averageServiceTime;
}

/** Gets the average service time
 * @return the average service time
 */
float Event::getAverageServiceTime() {
	return averageServiceTime;
}
