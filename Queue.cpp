//
// Created by sulli on 11/9/2021.
//

#include "Queue.h"
#include <typeinfo>

using namespace std;


void Queue::enQueue(process x) {

    // Create a new LL node
    QueueNode *temp = new QueueNode(x);

    // If queue is empty, then
    // new node is head and tail both
    if (tail == nullptr) {
        head = tail = temp;
        return;
    }

    // Add the new node at
    // the end of queue and change tail
    tail->next = temp;
    tail = temp;
}

// Function to remove
// a key from given queue q
void Queue::deQueue() {
    // If queue is empty, return NULL.
    if (head == nullptr)
        return;

    // Store previous head and
    // move head one node ahead
    QueueNode *temp = head;
    head = head->next;

    // If head becomes NULL, then
    // change tail also as NULL
    if (head == nullptr)
        tail = nullptr;

    delete (temp);
}

process Queue::peekQueue() {
    return head->data;
}

void Queue::deincrement(){
	head->data.burst--;
}

void Queue::age(){
	head->data.age++;
}

void Queue::setAge(int val){
	head->data.age=val;
}

void Queue::doWork(){
	head->data.worked++;
}

void Queue::setWork(int val){
	head->data.worked=val;
}

void Queue::ageQueue(){
	QueueNode *cur=head;
	while(cur!=nullptr){
		cur->data.age++;
		cur=cur->next;
	}
}

bool Queue::checkReal(){
	if(head==nullptr){
		return false;
	}
	return true;
}

process Queue::popQueue() {
    process returnProcess = peekQueue();
    deQueue();
    return returnProcess;
}

