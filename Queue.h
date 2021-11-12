#include <iostream>
#include "process.h"
#ifndef CS_452_LAB_02_QUEUE_H
#define CS_452_LAB_02_QUEUE_H


class QueueNode {
    process data;
    QueueNode *next;

    explicit QueueNode(process d) {
        data = d;
        next = nullptr;
    }
};

class Queue {
    void enQueue(process x);
    void deQueue();
    QueueNode *head, *tail;

    Queue() {
        head = tail = nullptr;
    }
};
#endif //CS_452_LAB_02_QUEUE_H
