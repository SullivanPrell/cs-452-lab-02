//
// Created by sulli on 11/11/2021.
//

#ifndef CS_452_LAB_02_PROCESS_H
#define CS_452_LAB_02_PROCESS_H
#include <iostream>

class process {
    public:
        int pid;
        int burst;
        int arrival;
        int priority;
        int deadline;
        int io;
        int queue;
		int age;
		int worked;
        int start;
        int completion_time;
        int waiting_time;
        int response_time;
        int turnaround_time;
};


#endif //CS_452_LAB_02_PROCESS_H
