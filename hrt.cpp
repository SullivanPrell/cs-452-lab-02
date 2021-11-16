//
// Created by sulli on 11/14/2021.
//

#include "hrt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "Queue.h"
#include "process.h"
#include <vector>
#include <algorithm>

using namespace std;


int tickCount = 0;

void hrt::performHardRealTime(std::vector<process> processes, int numProcess) {
    bool allProcessesComplete = false;
    int processesComplete = 0;
    int deadProcesses = 0;
    process currentProcess;
    // Sort by arrival time
    sort(processes.begin(), processes.end(), [](const process &lhs, const process &rhs) {
        return lhs.arrival < rhs.arrival;
    });
    // Begin HRT
    while (!allProcessesComplete) {
        if (processesComplete + deadProcesses == numProcess) {
            allProcessesComplete = true;
        } else {
            currentProcess = processes[processesComplete + deadProcesses];
            if (currentProcess.arrival == tickCount) {
                // Do work
            } else if (currentProcess.arrival < tickCount) {
                // Waiting
            } else if (currentProcess.arrival > tickCount && currentProcess.deadline > tickCount) {
                // Dead Process
            } else if(currentProcess.arrival > tickCount && currentProcess.deadline < tickCount) {
                // Past arrival before deadline preform work
            }
        }

    }
}