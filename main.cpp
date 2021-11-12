#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "Queue.h"
#include "process.h"
#include <vector>
using namespace std;

void mfqs(process raw, int arrCount);

void findWaitingTimeRoundRobin(process arr, int arrCount, int wt[], int quantum);

void findTurnAroundTimeRoundRobin(process arr, int arrCount, int wt[], int tat[]);

void findavgTimeRoundRobin(process arr, int arrCount, int quantum);

process findTail(process head);

void doWork(process head);

void srt(process arr, int arrCount);

void hrt(process arr, int arrCount);

void display(process proc);

void quickSort(process arr[], int low, int high);

int partition(process arr[], int low, int high);

void swap(process *a, process *b);

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Incorrect parameter number\n");
        return 0;
    }

    ifstream inputFile{argv[1]};
	vector<string> strings;

    string line;
    int ProcNum = 0;
    while (getline(inputFile, line)) {
        if (line.find('-') > line.length() && line.find('P') > line.length()) {
            strings.push_back(line);
            ProcNum++;
        }
    }

    //Closing file
    inputFile.close();

    process *arr = new process[ProcNum];
    printf("Arr made\n");

    for (int i = 1; i < ProcNum; i++) {
        line = strings[i];
        stringstream is(line);
        int n;
        is >> n;
        arr[i].pid = n;
        is >> n;
        arr[i].burst = n;
        is >> n;
        arr[i].arrival = n;
        is >> n;
        arr[i].priority = n;
        is >> n;
        arr[i].deadline = n;
        is >> n;
        arr[i].io = n;
    }

    bool select = false;
    string mode = "";
    while (!select) {
        cout << "Select mfqs, srt, or hrt\n";
        cin >> mode;
        if (mode == "mfqs") {
            mfqs(arr[0], ProcNum);
            select = true;
        } else if (mode == "srt") {
            srt(arr[0], ProcNum);
            select = true;
        } else if (mode == "hrt") {
            hrt(arr[0], ProcNum);
            select = true;
        }
    }

    cout << "Terminated Cleanly with " << ProcNum << " processes scheduled \n";
    return 0;
}

void mfqs(process raw, int arrCount) {
    int queues, quantum, age;

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
    }

}

void doWork(process head) {
    head.burst--;

}

void srt(process arr, int arrCount) {}

void hrt(process arr, int arrCount) {}

void display(process proc) {
    cout << proc.pid << " " << proc.burst << " " << proc.arrival << " " << proc.priority << " " << proc.deadline << " "
         << proc.io << "\n";
}

void swap(process *a, process *b) {
    process t = *a;
    *a = *b;
    *b = t;
}


void findWaitingTimeRoundRobin(process arr, int arrCount, int wt[], int quantum) {
    // Make a copy of burst times bt[] to store remaining
    // burst times.

    int *rem_bt = new int[arrCount];
    for (int i = 0; i < arrCount; i++)
        rem_bt[i] = arr.burst;

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
                    wt[i] = t - arr.burst;

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
void findTurnAroundTimeRoundRobin(process arr, int arrCount, int wt[], int tat[]) {
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < arrCount; i++)
        tat[i] = arr.burst + wt[i];
}

void findavgTimeRoundRobin(process arr, int arrCount, int quantum) {
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
        cout << " " << i + 1 << "\t\t" << arr.burst << "\t "
             << wt[i] << "\t\t " << tat[i] << endl;
    }

    cout << "Average waiting time = "
         << (float) total_wt / (float) arrCount;
    cout << "\nAverage turn around time = "
         << (float) total_tat / (float) arrCount;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(process arr[], int low, int high) {
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
void quickSort(process arr[], int low, int high) {
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