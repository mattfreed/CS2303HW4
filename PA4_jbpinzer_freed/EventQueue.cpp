/*
 * EventQueue.cpp
 *
 *  Created on: Feb 13, 2018
 *      Author: mwfreed
 */
#include "EventQueue.h"

/** Constructor for EventQueue
 */
EventQueue::EventQueue() {
	head = NULL;//initializes the head of the linked list to null
	tail = NULL;//initiiales the tail of the linked list to null
}

/** Destructor for EventQueue
 */
EventQueue::~EventQueue() {
	node* temp = new node();//create new node to hold temporary information
	temp=head;
	while(temp!=NULL){
		deleteFirst();
		temp=temp->next;
	}

	delete(temp);
}

/** Creates new event queue node and adds it to the end of the list
 * @param object is the Event object getting added to the list
 */
void EventQueue::createNode(Event *object) {
	node *temp = new node();//creates temporary node to hold information
	temp -> event = object;
	temp->next=NULL;
	if(head==NULL){
		head = temp;
		tail=temp;
		temp=NULL;
	}
	else
	{
		tail->next=temp;
		tail=temp;
	}
}

/** Inserts a node a specific position
 * @param pos is the position you want to add at
 * @param object is the object you wish to add
 */
void EventQueue::insert(int pos, Event *object) {//this will probably be used for sorting
	node *pre = new node();//create temporary node to hold previous information
	node *cur = new node();//create temporary node to hold current information
	node *temp = new node();//create temporary node to hold temporary information
	for(int i = 1; i < pos; i++){
		pre=cur;
		cur=cur->next;
	}
	//loop invariants: 1<=i<pos
	temp->event = object;
	pre->next=temp;
	temp->next=cur;

}

/** Deletes the first object in the list
 */
void EventQueue::deleteFirst() {
	node *temp = new node();//create temporary node
	temp=head;//set temporary node equal to head
	head=head->next;
	delete temp;
}

/** Deletes an object at a certain position in the list
 * @param pos is the position in the list you want to delete
 */
void EventQueue::deletePosition(int pos) {
	node *current = new node();//create temporary node to cold current info
	node *previous = new node();//create temporary node to hold previous info for comparison
	current=head;
	for(int i=1; i<pos;i++){
		previous=current;
		current=current->next;
	}
	//loop invariant 1<=i<pos
	previous->next=current->next;

	delete(current);
	delete(previous);
}

/** getFirst() returns the first Event in the linked list
 * @return the first event in the queue
 */
Event* EventQueue::getFirst() {
	return head->event;
}

/** Finds the first customer in the queue that has arrived
 * @param queue takes in the teller queue
 * @return the time the customer arrived if there was one, or the idle time the teller will take if not.
 */
float EventQueue::findCustomers(TellerQueue* queue) {
	node* current = head;//create temporary node to hold the head information
	while(current != NULL) {
		if(head->event->getStartTime() >= queue->getFirst()->getStartTime()) { //Customer is waiting
			float time = queue->getFirst()->getStartTime();
			queue->deleteFirst();
			head->event->setAction(2);
			return time;
		} else { //No customer waiting
			float idleTime = IDLE_MOD * rand()/float(RAND_MAX);
			head->event->setAction(3);
			head->event->setStartTime(head->event->getStartTime()+idleTime);
			return idleTime;
		}

		current = current -> next;
	}

	return -1; //if an error occurs
}

/** Sorts the entire queue
 */
void EventQueue::sortQueue(){
	for (node *nodeH = head; nodeH->next != NULL; nodeH = nodeH->next) {
	  for (node *nodeT = nodeH->next; nodeT != NULL; nodeT = nodeT->next) {
	    if (nodeH->event->getStartTime() > nodeT->event->getStartTime()) {
	      swap(nodeH->event, nodeT->event);
	    }
	  }
	}
}

/**Prints the entire queue
 */
void EventQueue::printQueue(){
	node* temp = new node();//create new node to hold temporary information
	temp=head;
	while(temp!=NULL){
		cout << "Teller "  << temp->event->getLine() << ": " << temp->event->getStartTime() << endl;
		temp=temp->next;
	}

	delete(temp);
}
