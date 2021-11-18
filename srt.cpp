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
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int idx;
    int n = arrCount;
    int tq = quantum;

    cout<<endl;
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<endl;
    for(int i = 0; i < n; i++) {
        burst_remaining[i] = arr[i].burst;
        cout<<arr[i].pid<<"\t"<<arr[i].arrival<<"\t"<<arr[i].burst<<"\t"<<arr[i].start<<"\t"<<arr[i].completion_time<<"\t"<<arr[i].turnaround_time<<"\t"<<arr[i].waiting_time<<"\t"<<arr[i].response_time<<"\t"<<"\n"<<endl;

    }


    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mark[n];
    memset(mark,0,sizeof(mark));
    mark[0] = 1;

while(completed != n) {
        idx = q.front();
        q.pop();

        if(burst_remaining[idx] == arr[idx].burst) {
            arr[idx].start = max(current_time,arr[idx].arrival);
            total_idle_time += arr[idx].start - current_time;
            current_time = arr[idx].start;
        }

        if(burst_remaining[idx]-tq > 0) {
            burst_remaining[idx] -= tq;
            current_time += tq;
        }
        else {
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;

            arr[idx].completion_time = current_time;
            arr[idx].turnaround_time = arr[idx].completion_time - arr[idx].arrival;
            arr[idx].waiting_time = arr[idx].turnaround_time - arr[idx].burst;
            arr[idx].response_time = arr[idx].start - arr[idx].arrival;

            total_turnaround_time += arr[idx].turnaround_time;
            total_waiting_time += arr[idx].waiting_time;
            total_response_time += arr[idx].response_time;
        }

        for(int i = 1; i < n; i++) {
            if(burst_remaining[i] > 0 && arr[i].arrival <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }
        if(burst_remaining[idx] > 0) {
            q.push(idx);
        }

        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }


    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    cpu_utilisation = ((arr[n-1].completion_time - total_idle_time) / (float) arr[n-1].completion_time)*100;

    cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
    cout<<"CPU Utilization = "<<cpu_utilisation<<"%"<<endl;

}
