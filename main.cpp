#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

void mfqs(Queue raw, int arrCount);

void findWaitingTimeRoundRobin(vector<process> arr, int arrCount, int wt[], int quantum);

void findTurnAroundTimeRoundRobin(vector<process> arr, int arrCount, int wt[], int tat[]);

void findavgTimeRoundRobin(vector<process> arr, int arrCount, int quantum);

process findTail(process head);

void doWork(process head);

void srt(vector<process> arr, int arrCount);

void hrt(process arr[], int arrCount);

void display(process proc);

void quickSort(process arr[], int low, int high);

int partition(vector<process> arr, int low, int high);

void swap(process *a, process *b);

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Incorrect parameter number\n");
        return 0;
    }

    ifstream fileIn{argv[1]};
    vector<process> processes;
    int numProcess = 0;
    string rawString;
    int parsedInt;
    process tempProcess;
    while (!fileIn.eof()) {
        if (numProcess > 0) {
            fileIn >> rawString; //PID
            parsedInt = std::stoi(rawString);
            tempProcess.pid = parsedInt;

            fileIn >> rawString; //BST
            parsedInt = std::stoi(rawString);
            tempProcess.burst = parsedInt;

            fileIn >> rawString; //ARR
            parsedInt = std::stoi(rawString);
            tempProcess.arrival = parsedInt;

            fileIn >> rawString; //PRI
            parsedInt = std::stoi(rawString);
            tempProcess.priority = parsedInt;

            fileIn >> rawString; //DLINE
            parsedInt = std::stoi(rawString);
            tempProcess.deadline = parsedInt;

            fileIn >> rawString; //IO
            parsedInt = std::stoi(rawString);
            tempProcess.io = parsedInt;

            processes.push_back(tempProcess);
        } else {
            fileIn >> rawString;
            fileIn >> rawString;
            fileIn >> rawString;
            fileIn >> rawString;
            fileIn >> rawString;
            fileIn >> rawString;
        }
        ++numProcess;
    }
    fileIn.close();

    sort(processes.begin(), processes.end(), [](const process &lhs, const process &rhs) {
        return lhs.arrival < rhs.arrival;
    });

    bool select = false;
    string mode = "mfqs";
    while (!select) {
        //cout << "Select mfqs, srt, or hrt\n";
        //cin >> mode;
        if (mode == "mfqs") {
            Queue prime;
            for (int i = 0; i < numProcess; i++) {
                prime.enQueue(processes[i]);
            }
            mfqs(prime, numProcess);
            select = true;
        } else if (mode == "srt") {
            srt(processes, numProcess);
            select = true;
        } else if (mode == "hrt") {
//            hrt(arr, numProcess);
            select = true;
        }
    }

    cout << "Terminated Cleanly with " << numProcess << " processes scheduled \n";
    return 0;
}

void mfqs(Queue prime, int arrCount) {
    int queues = 5;
    int quantum = 4;
    int age = 5;
    /*
    while (1) {
        cout << "How many queues will be generated\n";
        cin >> queues;
        if (cin.fail() || queues < 2 || queues > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (1) {
        cout << "What is the time quantum\n";
        cin >> quantum;
        if (cin.fail() || quantum < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    while (1) {
        cout << "How long should processes take to age up\n";
        cin >> age;
        if (cin.fail() || age < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }*/

    Queue *things = new Queue[queues];
    int clocktick = 0;
    int workDone = 0;
    int i = 0;
    int context = -1;
    int procDone = 0;
    int queued = 0;
    int modQuantum;
    printf("We have %d procs\n", arrCount);

    while (1) {
        //checks to see if everything is queued. if not it adds all items that have arrived
        //at the current clock tick
        if (queued < arrCount) {
            while (queued < arrCount && prime.peekQueue().arrival == clocktick) {
                process tmp = prime.popQueue();
                things[0].enQueue(tmp);
                queued++;
            }
        }
        //determines the first queue to have contents
        for (i = 0; i < queues; i++) {
            if (things[i].head != nullptr) {
                break;
            }
        }

        //checks to make sure we are in valid queues.
        //The only time this is relevant is if all queues are empty

        if (i == queues) {
            clocktick++;
            continue;
        }

        //checks to see if current queue is the same as last loop.
        //if not it resets the timer for demotions
        if (context != i) {
            //workDone=0;
            context = i;
            modQuantum = quantum * pow(2, i);
        }

        things[i].deincrement();
        things[i].doWork();
        //workDone++;

        if (things[i].peekQueue().burst == 0) {
            process tmp = things[i].popQueue();
            procDone++;
            //workDone=0;
            printf("Process %d terminated in queue %d\n", tmp.pid, i + 1);

        } else if (things[i].peekQueue().worked == modQuantum && i < queues - 1) {
            process tmp = things[i].popQueue();
            //printf("%d demoted to %d\n",tmp.pid,i+1);
            tmp.worked = 0;
            things[i + 1].enQueue(tmp);
            //workDone=0;
        } else if (i == queues - 1) {
            if (things[i].peekQueue().age == age) {
                process tmp = things[i].popQueue();
                tmp.age = 0;
                printf("%d promoted\n", tmp.pid);
                things[i - 1].enQueue(tmp);
            } else {
                things[i].age();
            }
        }
        clocktick++;
        if (procDone == arrCount) {
            break;
        }
    }
}


void doWork(process head) {
    head.burst--;
}

void srt(vector<process> arr, int arrCount) {
    int time;
    cout << "What would you like the time quantum to be?\n";
    cin >> time;
    cout << "Starting soft real time round robin:\n";
    findavgTimeRoundRobin(arr, arrCount, time);
}

void hrt(process arr[], int arrCount) {}

void display(process proc) {
    cout << proc.pid << " " << proc.burst << " " << proc.arrival << " " << proc.priority << " " << proc.deadline << " "
         << proc.io << "\n";
}

void swap(process *a, process *b) {
    process t = *a;
    *a = *b;
    *b = t;
}


void findWaitingTimeRoundRobin(vector<process> arr, int arrCount, int wt[], int quantum) {
    // Make a copy of burst times bt[] to store remaining
    // burst times.

    int *rem_bt = new int[arrCount];
    for (int i = 0; i < arrCount; i++)
        rem_bt[i] = arr[i].burst;

    int t = 0; // Current time

    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1) {
        bool done = true;

        // Traverse all processes one by one repeatedly
        for (int i = 0; i < arrCount; i++) {
            // If burst time of a process is greater than 0
            // then only need to process further
            if (rem_bt[i] > 0) {
                done = false; // There is a pending process

                if (rem_bt[i] > quantum) {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t += quantum;

                    // Decrease the burst_time of current process
                    // by quantum
                    rem_bt[i] -= quantum;
                }

                    // If burst time is smaller than or equal to
                    // quantum. Last cycle for this process
                else {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t = t + rem_bt[i];

                    // Waiting time is current time minus time
                    // used by this process
                    wt[i] = t - arr[i].burst;

                    // As the process gets fully executed
                    // make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
            }
        }

        // If all processes are done
        if (done == true)
            break;
    }
}

// Function to calculate turn around time
void findTurnAroundTimeRoundRobin(vector<process> arr, int arrCount, int wt[], int tat[]) {
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < arrCount; i++)
        tat[i] = arr[i].burst + wt[i];
}

void findavgTimeRoundRobin(vector<process> arr, int arrCount, int quantum) {
    int *wt = new int[arrCount];
    int *tat = new int[arrCount];
    int total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTimeRoundRobin(arr, arrCount, wt, quantum);

    // Function to find turn around time for all processes
    findTurnAroundTimeRoundRobin(arr, arrCount, wt, tat);

    // Display processes along with all details
    cout << "Processes " << " Burst time "
         << " Waiting time " << " Turn around time\n";

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < arrCount; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i + 1 << "\t\t" << arr[i].burst << "\t "
             << wt[i] << "\t\t " << tat[i] << endl;
    }

    cout << "Average waiting time = "
         << (float) total_wt / (float) arrCount;
    cout << "\nAverage turn around time = "
         << (float) total_tat / (float) arrCount << "\n";
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(vector<process> arr, int low, int high) {
    int pivot = arr[high].arrival;    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j].arrival <= pivot) {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(vector<process> arr, int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}