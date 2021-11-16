#include "hrt.h"
#include "Queue.h"
#include <vector>
#include <algorithm>

using namespace std;


int tickCount = 0;

void hrt::performHardRealTime(std::vector<process> processes, int numProcess) {
    bool allProcessesComplete = false;
    int processesComplete = 0;
    process currentProcess;
    // Sort by arrival time
    sort(processes.begin(), processes.end(), [](const process &lhs, const process &rhs) {
        return lhs.arrival < rhs.arrival;
    });
    // Begin HRT
    while (!allProcessesComplete) {
        if (processesComplete == numProcess) {
            allProcessesComplete = true;
        } else {
            currentProcess = processes[processesComplete];
            if (currentProcess.arrival == tickCount ||
                (currentProcess.arrival < tickCount && currentProcess.deadline < tickCount)) {
                // On arrival or past arrival BUT before deadline
                // Do work
                if (currentProcess.io > 0) {
                    // Handle I/O
                    //TODO: How to handle I/O
                } else {
                    // No I/O
                    if (currentProcess.deadline <= tickCount + currentProcess.burst) {
                        tickCount += currentProcess.burst;
                        processesComplete++;
                        continue;
                    } else {
                        break;
                    }
                }
            } else if (currentProcess.arrival < tickCount) {
                // Waiting
                tickCount++;
                continue;
            } else if (currentProcess.arrival > tickCount && currentProcess.deadline > tickCount) {
                // Dead Process
                break;
            }
        }
    }
    printf("\ncompleted processes: %d",processesComplete);
}