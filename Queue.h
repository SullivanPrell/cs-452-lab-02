#include <iostream>
#ifndef CS_452_LAB_02_QUEUE_H
#define CS_452_LAB_02_QUEUE_H


struct QueueNode {
    int data;
    QueueNode *next;

    explicit QueueNode(int d) {
        data = d;
        next = nullptr;
    }
};

struct Queue {
    void enQueue(int x);
    void deQueue();
    QueueNode *head, *tail;

    Queue() {
        head = tail = nullptr;
    }
};
#endif //CS_452_LAB_02_QUEUE_H
