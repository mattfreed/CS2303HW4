/*
 * TellerQueue.h
 *
 *  Created on: Feb 14, 2018
 *      Author: jbpinzer
 */

#ifndef TellerQueue_H_
#define TellerQueue_H_

#include <iostream>
#include <typeinfo>

#include "Event.h"

using namespace std;

class TellerQueue
{
	public:
		TellerQueue();
		~TellerQueue();

		void createNode(Event *object);
		void insert(int pos, Event *object);

		void deleteFirst();

		Event* getFirst();

		int getLength();

		void deletePosition(int pos);
		void sortQueue();
		void printQueue();



	private:
		struct node{
			Event *event = NULL;
			node *next = NULL;
		};

		node *head , *tail;

};



#endif /* TellerQueue_H_ */
