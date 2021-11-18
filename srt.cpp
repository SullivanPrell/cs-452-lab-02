#include <vector>
#include <algorithm>
#include <cmath>
#include "srt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <queue>
#include <iomanip>
#include <cstring>

using namespace std;


void srt::dosrt(std::vector<process> arr, int arrCount, int quantum) {
    bool ProcsCompleted = false;
    int completed = 0;
    process currentProcess;
    int burstRemaining[arrCount];
    float avg_turnaround_time;
    float avg_waiting_time;
    long total_turnaround_time = 0;
    long total_waiting_time = 0;
    int currentTime = 0;

    for (int i = 0; i < arrCount; i++) {
        burstRemaining[i] = arr[i].burst;
    }

    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    while (ProcsCompleted == false) {
        if (completed == arrCount) {
            ProcsCompleted = true;
        } else {
            currentProcess = arr[completed];
            if (burstRemaining[completed] > 0) {
                burstRemaining[completed] -= quantum;
                currentTime += quantum;
            } else {
                cout<<arr[completed].pid<<"\t"<<arr[completed].arrival<<"\t"<<arr[completed].burst<<"\t"<<arr[completed].turnaround_time<<"\t"<<arr[completed].waiting_time;
                currentTime += burstRemaining[completed];
                burstRemaining[completed] = 0;
                arr[completed].completion_time = currentTime;
                arr[completed].waiting_time = arr[completed].turnaround_time - arr[completed].burst;
                total_turnaround_time += arr[completed].turnaround_time;
                total_waiting_time += arr[completed].waiting_time;
                completed++;

            }
        }

    }

    avg_turnaround_time = (float) total_turnaround_time / arrCount;
    avg_waiting_time = (float) total_waiting_time / arrCount;

    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
}
