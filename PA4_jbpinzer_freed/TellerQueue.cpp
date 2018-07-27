/*
 * TellerQueue.cpp
 *
 *  Created on: Feb 13, 2018
 *      Author: mwfreed
 */
#include "TellerQueue.h"

/** Constructor for TellerQueue
 */
TellerQueue::TellerQueue() {
	head = NULL;//sets the head of the linked list to null
	tail = NULL;//sets the tail of the linked list to null
}
/** Destructor for TellerQueue
 */
TellerQueue::~TellerQueue() {
	node* temp = new node();//create new node to hold temporary information
	temp=head;
	while(temp!=NULL){
		deleteFirst();
		temp=temp->next;
	}

	delete(temp);
}

/** Creates a new event queue node and adds it to the end of the list
 * @param object is the Event object getting added to the list
 */
void TellerQueue::createNode(Event *object) {
	node *temp = new node();//creates a new temporary node to hold information
	temp -> event = object;//sets the temp node to contain the current even
	temp->next=NULL;//sets the current next to the temp next
	if(head==NULL){//check if head is null
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

/** Inserts an Event a specific position
 * @param pos is the position you want to add at
 * @param object is the object you wish to add
 */
void TellerQueue::insert(int pos, Event *object) {
	node *pre = new node();//creates new node to hold previous
	node *cur = new node();//creates new node for the current
	node *temp = new node();//creates new node for the temporary hold
	for(int i = 1; i < pos; i++){
		pre=cur;
		cur=cur->next;
	}
	//loop invariants: i>=1 i<pos
	temp->event = object;
	pre->next=temp;
	temp->next=cur;

}

/** Deletes the first object in the list
 */
void TellerQueue::deleteFirst() {
	node *temp = new node();//create new temporary node
	temp=head;//set the temp = head
	head=head->next;
	delete temp;
}

/** Gets the first event of the linked list of the teller queue
 * @return the first event in the queue
 */
Event* TellerQueue::getFirst() {
	return head->event;
}

/** Gets the length of the teller queue
 * @return an integer of the teller queue length
 */
int TellerQueue::getLength() {
	int length = 0; //initialize length to 0
	node* temp = new node(); //create a temporary node to hold information
	temp=head;
	while(temp!=NULL){
		length++;
		temp=temp->next;
	}
	return length;
}

/** Deletes an object at a certain position in the list
 * @param pos is the position of the list you want to delete
 */
void TellerQueue::deletePosition(int pos) {
	node *current = new node();
	node *previous = new node();
	current=head;
	for(int i=1; i<pos;i++){
		previous=current;
		current=current->next;
	}
	previous->next=current->next;

	delete(current);
	delete(previous);
}

/** Sorts the entire queue
 */
void TellerQueue::sortQueue(){
	for (node *nodeH = head; nodeH->next != NULL; nodeH = nodeH->next) {
	  for (node *nodeT = nodeH->next; nodeT != NULL; nodeT = nodeT->next) {
	    if (nodeH->event->getStartTime() > nodeT->event->getStartTime()) {
	      swap(nodeH->event, nodeT->event);
	    }
	  }
	}
}

/** Prints the entire queue
 */
void TellerQueue::printQueue(){
	node* temp = new node();
	temp=head;
	while(temp!=NULL){
		cout << temp->event->getStartTime() << endl;

		temp=temp->next;
	}

	delete(temp);
}
