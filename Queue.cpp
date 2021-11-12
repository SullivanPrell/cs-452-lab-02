//
// Created by sulli on 11/9/2021.
//

#include "Queue.h"
#include <typeinfo>

using namespace std;


void Queue::enQueue(int x) {

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

