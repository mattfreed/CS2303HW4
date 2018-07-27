#include "Simulator.h"

/** Constructs a Simulator
 * @param numCustomers how many customers will come to the bank
 * @param numTellers how many tellers are working at the bank
 * @param simTime how long the simulation should run for, will never pass this number even if there are customers left
 * @param averageServiceTime the average time that a teller provides service
 */
Simulator::Simulator(int numCustomers, int numTellers, float simTime, float averageServiceTime) {
	this->numCustomers = numCustomers;
	this->numTellers = numTellers;
	this->simTime = simTime;
	this->averageServiceTime = averageServiceTime;

	//Initialize variables
	queueType = "Unknown Queue Type";
	customersServed = 0;
	timeSpentServing = 0;
	avgTime = 0;
	stdDev = 0;
	maxWaitTime = 0;
	totalTimeInBank = 0;
	totalTellerServiceTime = 0;
	totalTellerIdleTime = 0;

}

/** Runs the simulation for one line, where each customer can go to whatever teller is free
 */
void Simulator::runCommonLine() {
	queueType = "Common Line"; //Define the type of queue

	Clock clk = Clock(); //Create a clock to keep track of time
	EventQueue *queue = new EventQueue(); //Create the queue of events
	TellerQueue *tellerQueue = new TellerQueue(); //Create the queue of customers for the teller

	//Loop through each customer that will come to the store and create them, then add them to the teller queue.
	for(int i = 0; i < numCustomers; i++) {
		Event* c = new Event(simTime * rand()/float(RAND_MAX));
		tellerQueue->createNode(c);

	}
	tellerQueue->sortQueue(); //Sort the queue

	clk.setTime(tellerQueue->getFirst()->getStartTime()); //Set the starting time to the time of the first customer

	//Loop through each teller to create one and add it to the event queue
	for(int j = 0; j < numTellers; j++) {
		Event* t = new Event();
		queue->createNode(t);
	}

	float listOfTimeInBank[numCustomers]; //Keep track of every customer's time spent in the bank, for calculations later
	float startTime = 0; //Init startTime at 0
	float waitTime = 0; //Init waitTime at 0

	//Loop using a while loop until either the time has passed the simulation time, or all of the customers have been serviced
	while(clk.getTime() <= simTime && customersServed < numCustomers) {
		//Set the action back to waiting if set for something else.
		if(queue->getFirst()->getAction() == 2) {
			queue->getFirst()->setAction(1);
		} else if(queue->getFirst()->getAction() == 3) {
			queue->getFirst()->setAction(1);
		}

		//Make sure the teller is ready to serve
		if(queue->getFirst()->getAction() == 1) {
			startTime = queue->findCustomers(tellerQueue); //find the first customer available to serve if the time has come.
			if(queue->getFirst()->getAction() == 3) {
				//Currently idling, so startTime is actually idleTime
				totalTellerIdleTime += startTime;
			} else if(queue->getFirst()->getAction() == 2) {
				//Currently serving a customer
				float serveTime = queue->getFirst()->getStartTime() - startTime;
				timeSpentServing += serveTime;
				totalTimeInBank += (waitTime + serveTime);

				listOfTimeInBank[customersServed-1] = (waitTime + serveTime); //set the customer's time spent in the bank

				//We know a customer was called to be serviced. Start time, is when they arrived at the bank
				waitTime = queue->getFirst()->getStartTime() - startTime; //how long customer was waiting.
				float timeToService = 2*averageServiceTime*rand()/float(RAND_MAX);

				totalTellerServiceTime += timeToService;

				queue->getFirst()->setStartTime(queue->getFirst()->getStartTime() + timeToService);

			}

			if(queue->getFirst()->getAction() == 2) { //Now servicing a customer
				customersServed++; //served another customer
				//if this customer was waiting longer than the previous record, overwrite it
				if(waitTime > maxWaitTime) {
					maxWaitTime = waitTime;
				}
				queue->sortQueue(); //sort the tellers
				if(customersServed < numCustomers){
					clk.setTime(tellerQueue->getFirst()->getStartTime());
				}
			}

		} else {
			//ERROR - action isn't waiting for a customer, it should be.
		}
		queue->sortQueue(); //sort at the end of the loop
	}

	avgTime = totalTimeInBank/customersServed; //Calculate the average time spent in the bank.

	//Calculate the numerator to calculate variance to then calculate stdDev
	float varNumerator = 0;
	for(int i = 0; i < customersServed; i++) {
		varNumerator += pow(listOfTimeInBank[i] - avgTime, 2);
	}


	stdDev = sqrt(varNumerator/customersServed); //Calculate standard deviation

	//Delete both queues
	delete(queue);
	delete(tellerQueue);
}

/** Run the simulation as if each teller had their own line of customers
 */
void Simulator::runIndividualLine() {
	queueType = "Line for each Teller"; //the type of queue

	Clock clk = Clock();
	EventQueue *queue = new EventQueue();
	TellerQueue *tellerQueue = new TellerQueue[numTellers]; //Create an array of teller queues for each teller.


	//Create each teller and give them a line
	for(int i = 0; i < numTellers; i++) {
		Event* t = new Event();
		t->setLine(i);
		queue->createNode(t);
	}

	//Create each customer, and put them in the shortest line they find
	for(int j = 0; j < numCustomers; j++) {
		Event* c = new Event(simTime * rand()/float(RAND_MAX));
		int shortestLine = getShortestLine(tellerQueue, numTellers);
		tellerQueue[shortestLine].createNode(c);

	}

	float listOfTimeInBank[numCustomers];
	float startTime = 0;
	float waitTime = 0;
	float customersServedInLine = 0;

	for(int k = 0; k < numTellers; k++) {
		tellerQueue[k].sortQueue();

		int lineLength = tellerQueue[k].getLength(); //Store the original length of the line so the while loop can terminate

		clk.setTime(tellerQueue[k].getFirst()->getStartTime());

		//Loop using a while loop to make sure the clock is less than the simulation max time and the last thing in the queue isnt above the max time
		// also to check that the customers being served in this line is less than the length for this line
		while(clk.getTime() <= simTime && queue->getFirst()->getStartTime() <= simTime && customersServedInLine < lineLength) {
			if(queue->getFirst()->getAction() == 2) {
				queue->getFirst()->setAction(1);
			} else if(queue->getFirst()->getAction() == 3) {
				queue->getFirst()->setAction(1);
			}
			if(queue->getFirst()->getAction() == 1) {
				startTime = queue->findCustomers(&tellerQueue[k]);
				if(queue->getFirst()->getAction() == 3) {
					//Currently idling, so startTime is actually idleTime
					totalTellerIdleTime += startTime;
				} else if(queue->getFirst()->getAction() == 2) {

					float serveTime = queue->getFirst()->getStartTime() - startTime;
					timeSpentServing += serveTime;
					totalTimeInBank += (waitTime + serveTime);

					listOfTimeInBank[customersServed-1] = (waitTime + serveTime);

					//We know a customer was called to be serviced. Start time, is when they arrived at the bank
					waitTime = queue->getFirst()->getStartTime() - startTime; //how long customer was waiting.
					float timeToService = 2*averageServiceTime*rand()/float(RAND_MAX);

					totalTellerServiceTime += timeToService;

					queue->getFirst()->setStartTime(queue->getFirst()->getStartTime() + timeToService);

				}

				if(queue->getFirst()->getAction() == 2) { //Now servicing a customer
					customersServedInLine++;
					customersServed++;
					if(waitTime > maxWaitTime) {
						maxWaitTime = waitTime;
					}
					if(tellerQueue[k].getLength() > 0) {
						clk.setTime(tellerQueue[k].getFirst()->getStartTime());
					}
				}

			} else {
				//ERROR
			}
		}
		customersServedInLine = 0;
		queue->sortQueue();


	}

	avgTime = totalTimeInBank/customersServed;

	float varNumerator = 0;
	for(int i = 0; i < customersServed; i++) {
		varNumerator += pow(listOfTimeInBank[i] - avgTime, 2);
	}

	stdDev = sqrt(varNumerator/customersServed);

	//Delete both queues to free up memory
	delete(queue);
	delete[](tellerQueue);

}

/** Reset the statistics for when switching from common line to individual line
 */
void Simulator::reset() {
	queueType = "Unknown Queue Type";
	customersServed = 0;
	timeSpentServing = 0;
	avgTime = 0;
	stdDev = 0;
	maxWaitTime = 0;
	totalTimeInBank = 0;
	totalTellerServiceTime = 0;
	totalTellerIdleTime = 0;
}

/** Print the simulation statistics
 */
void Simulator::printStats(){
	cout << "Statistics for a " << queueType << "." << endl;
	cout << "There were " << numTellers << " tellers that served " << customersServed << " customers over "
			<< timeSpentServing << " seconds." << endl;
	cout << "The average customer spent " << avgTime << " seconds in the bank with a standard deviation of +/- "
			<< stdDev << "." << endl;
	cout << "The longest time a customer waited to be served was " << maxWaitTime << "." << endl;
	cout << "The tellers spent a total of " << totalTellerServiceTime << " seconds serving customers and a total of "
			<< totalTellerIdleTime << " seconds spent idle." << endl;
}

/** Get the shortest line
 * @param queue[] the array of teller queues to go through
 * @param length the number of teller queues there are
 * @returns an integer for the index of the shortest line (teller queue)
 */
int Simulator::getShortestLine(TellerQueue queue[], int length) {
	int shortestLine = 0;
	int shortestLength = queue[0].getLength();

	for(int i = 0; i < length; i++) {
		if(queue[i].getLength() < shortestLength) {
			shortestLine = i;
		}
	}

	return shortestLine;

}
