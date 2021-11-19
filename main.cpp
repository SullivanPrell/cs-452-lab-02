#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include "mfqs.h"
#include "rt.h"

using namespace std;


int partition(vector<process> arr, int low, int high);

void swap(process *a, process *b);

void display(process proc);

void supersort(vector<process> prioritySort);

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Incorrect parameter number\n");
        return 0;
    }
    printf("Assembling processes\n");
    ifstream fileIn{argv[1]};
    vector<process> processes;
    int numProcess = 0;
    string rawString;
    int parsedInt;
    process tempProcess;
    string line;
    int n;
    while (getline(fileIn, line)) {
        if (line.find('-') > line.length() && line.find('P') > line.length()) {
            stringstream is(line);
            is >> n;
            tempProcess.pid = n;
            is >> n;
            tempProcess.burst = n;
            is >> n;
            tempProcess.arrival = n;
            is >> n;
            tempProcess.priority = n;
            is >> n;
            tempProcess.deadline = n;
            is >> n;
            tempProcess.io = n;
            tempProcess.age = 0;
            tempProcess.queue = 0;
            tempProcess.worked = 0;
            tempProcess.trueBurst = tempProcess.burst;
            if (tempProcess.pid < 0 || tempProcess.burst < 0 || tempProcess.arrival < 0 || tempProcess.deadline < 0 ||
                tempProcess.io < 0 || tempProcess.priority < 0) {
                //ignore
            } else {
                tempProcess.age = 0;
                tempProcess.queue = 0;
                tempProcess.worked = 0;
                processes.push_back(tempProcess);
                numProcess++;
            }
        }
    }
    fileIn.close();

    bool select = false;
    string mode;

    sort(processes.begin(), processes.end(), [](const process &lhs, const process &rhs) {
        return lhs.arrival < rhs.arrival;
    });
    while (!select) {
        cout << "Select mfqs, srt, or hrt\n";
        cin >> mode;
        if (mode == "mfqs") {

            Queue prime;
            for (int i = 0; i < numProcess; i++) {
                prime.enQueue(processes[i]);
            }
            mfqs::doQueues(prime, numProcess);
            select = true;
        } else if (mode == "srt") {
            int time;
            cout << "Starting soft real time scheduling:\n";
            rt::dosrt(processes, numProcess);
            select = true;

        } else if (mode == "hrt") {
            rt::performHardRealTime(processes, numProcess);
            select = true;
        }
    }
    return 0;
}

void doWork(process head) {
    head.burst--;
}


void display(process proc) {
    cout << proc.pid << " " << proc.burst << " " << proc.arrival << " " << proc.priority << " " << proc.deadline << " "
         << proc.io << "\n";
}

void swap(process *a, process *b) {
    process t = *a;
    *a = *b;
    *b = t;
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

void mfqs(Queue prime, int arrCount) {
    mfqs::doQueues(prime, arrCount);
}