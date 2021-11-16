#include "hrt.h"
#include "Queue.h"
#include <vector>
#include <algorithm>

using namespace std;


int tickCount = 0;

void hrt::performHardRealTime(std::vector<process> &processes, int numProcess) {
    bool allProcessesComplete = false;
    int processesComplete = 0;
    process currentProcess;

    printf("\ndebug1\n");
    // Begin HRT
    while (!allProcessesComplete) {
        printf("\ndebug1.5\n");
        if (processesComplete == numProcess) {
            printf("\nproblem\n");
            allProcessesComplete = true;
        } else {
            printf("\ndebug1.6\n");
            currentProcess = processes[processesComplete];
            if (currentProcess.arrival == tickCount ||
                (currentProcess.arrival < tickCount && currentProcess.deadline > tickCount)) {
                printf("\ndebug2\n");
                // On arrival or past arrival BUT before deadline
                // Do work
                printf("\n%d | %d",currentProcess.deadline, tickCount + currentProcess.burst);
                if (currentProcess.deadline >= (tickCount + currentProcess.burst)) {
                    tickCount += currentProcess.burst;
                    processesComplete++;
                    continue;
                } else {
                    printf("\ndebug6.5\n");
                    break;
                }
            } else if (currentProcess.arrival > tickCount) {
                // Waiting
                printf("\ndebug5\n");
                tickCount++;
                continue;
            } else if (currentProcess.deadline < tickCount) {
                // Dead Process
                printf("\ndebug6\n");
                printf("\n%d | %d",currentProcess.deadline, tickCount + currentProcess.burst);
                break;
            } else {
                printf("\nproblem pt2 %d %d", tickCount, currentProcess.pid);
            }
        }
    }
    printf("\ncompleted processes: %d", processesComplete);
}