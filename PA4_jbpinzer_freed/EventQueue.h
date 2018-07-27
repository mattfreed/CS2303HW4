/*
 * EventQueue.h
 *
 *  Created on: Feb 14, 2018
 *      Author: jbpinzer
 */

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <iostream>
#include <typeinfo>

#include "Event.h"
#include "TellerQueue.h"

using namespace std;

class EventQueue
{
	public:
		EventQueue();
		~EventQueue();

		void createNode(Event *object);
		void insert(int pos, Event *object);

		float findCustomers(TellerQueue* queue);

		Event* getFirst();

		void deleteFirst();

		void deletePosition(int pos);
		void sortQueue();
		void printQueue();



	private:
		struct node{
			Event *event = NULL;
			node *next = NULL;
		};

		node *head , *tail;

		static const float IDLE_MOD = 600;

};

#endif /* EVENTQUEUE_H_ */
