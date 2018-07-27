#include <iostream>
#include <cstdlib>
#include "Simulator.h"

using namespace std;

/*Total number of customers served and total time required to serve all customers
-Number of tellers and type of queuing (one per teller or common)
-Average (i.e., mean) amount of time a customer spent in the bank and the standard deviation
-Maximum wait time from the time a customer arrives to the time he/she is seen by a teller.
-Total amount of teller service time and total amount of teller idle time.
*/

/** The main program function
 * @param argc the count of args in the command line
 * @param argv an array of the characters from the command line
 * @return 0 if successful
 */
int main(int argc, char** argv) {

	//get inputs from command line/arguments
	if(argc == 6) { //if 6 then use a seed
		srand(atoi(argv[5]));
	} else if(argc < 5 || argc > 6){ //too few or too many args
		cout << "Incorrect number of command arguments - Usage\n" <<
				"\t./qSim #customers #tellers simulationTime averageServiceTime <seed>" << endl;
		return -1;
	} else { //seed the random number generator from the time
		srand(time(NULL));
	}

	int customers = atoi(argv[1]), tellers = atoi(argv[2]);//convert the inputs to integers

	double simulationTime = atol(argv[3]) * 60, averageServiceTime = atol(argv[4]) * 60;

	Simulator simulator = Simulator(customers, tellers, simulationTime, averageServiceTime);//run the simulator

	simulator.runCommonLine();
	simulator.printStats();

	simulator.reset();
	simulator.runIndividualLine();
	cout << endl;
	simulator.printStats();

	return 0;
}
