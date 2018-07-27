/*
 * Simulator.h
 *
 *  Created on: Feb 12, 2018
 *      Author: jbpinzer
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <iostream>
#include <cstdlib>
#include <math.h>

#include "Event.h"
#include "Clock.h"
#include "EventQueue.h"
#include "TellerQueue.h"

using namespace std;

class Simulator {
	public:
		Simulator(int numCustomers, int numTellers, float simTime, float averageServiceTime);
		void runCommonLine();
		void runIndividualLine();
		void printStats();
		void reset();

		int getShortestLine(TellerQueue queue[], int length);

	private:
		//initial data
		int numCustomers;
		int numTellers;
		string queueType;
		float simTime;
		float averageServiceTime;

		//statistics
		int customersServed;
		float timeSpentServing;
		float avgTime, stdDev, maxWaitTime;
		float totalTimeInBank, totalTellerServiceTime, totalTellerIdleTime;
};


#endif /* SIMULATOR_H_ */
