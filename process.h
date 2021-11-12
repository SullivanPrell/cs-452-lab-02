//
// Created by sulli on 11/11/2021.
//

#ifndef CS_452_LAB_02_PROCESS_H
#define CS_452_LAB_02_PROCESS_H


struct process {
    int pid;
    int burst;
    int arrival;
    int priority;
    int deadline;
    int io;
    int queue;
};


#endif //CS_452_LAB_02_PROCESS_H
