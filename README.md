# CS2303HW4
HW4 for CS2303 Systems Programming

Julian Pinzer 
Matthew Freed

CS 2303

Bank Simulation


Program Summary:

	This programs simulates a bank with customers entering and tellers completeing requests of customers. This program runs 2 trials, 1 with a single line of customers with tellers pulling from 1 line and another trial where each teller has their own individual line. Customers have arrival times and get added to a teller queue where seems fit. Tellers either take a customer or have an idle time for their "break". 
	
	This program creates a set of statistics: 
	-Total number of customers served and total time required to serve all customers
	-Number of tellers and the type of queueing (1 line or multiple lines)
	-Average amount of time a customer spent in bank and the standard deviation
	-Maximum wait time from the time a customer arives to the time he/she is seen by the teller
	-Totoal amount of teller service time and total amount of teller idle time

Build the program:
	'make clean' in the directory first.
	then just 'make' to build it.

Running the Program:

	To run the program, use the command ./qsim X Y W S <seed>

	-qsim is the file name
	-X is the amount customers
	-Y is the amount of tellers
	-W is the amount of time you want the sim to simulate(in minutes)
	-S is the average service time
	-<seed> is a seed for the random number generation, it is optional

Analysis:
	It appears that the common line is a lot better than the individual ones, more customers get served in the same time, and they wait less on average.

Problems encountered:
	The biggest issue we encountered waas with class hierarchy. We were attempting to have our Event class be a bass class for our customerEvent and TellerEvent classes. When adding the customerevents to a linkedlist of type Event, the data was being spliced and we were unable to access everything that we wanted.

Loop Invariants:
EventQueue:
		insert: 1<=i<pos
		deletePosition: 1<=i<pos
	
	TellerQueue:
		insert: 1<=i<pos
		deletePosition: 1<=i<pos

	Simulator:
		runCommonLine:
			0<=i< number of customers
			0<=j<number of customers
			0<=i<customers served
		runIndividualLines:
			0<=i<number of tellers
			0<=j<number of customers
			0<=i<number of tellers
			0<=k<number of tellers
			0<=i<customers served
		getShortestLine:
			0<=i<length of the line
