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


void srt::dosrt(std::vector<process> arr, int arrCount) {
    bool ProcsCompleted = false;
    int completed = 0;
    long avg_turnaround_time;
    long avg_waiting_time;
    long total_turnaround_time = 0;
    long total_waiting_time = 0;
    int currentTime = 0;
    vector<process> waiting;
    waiting.reserve(arrCount);
    int passed = 0;
    int failed = 0;

    while (ProcsCompleted == false) {
        if (completed == arrCount) {
            ProcsCompleted = true;
        } else {
            int cur = 0;
            while ( (arr.size()>0) && (arr[0].arrival==currentTime) ){
                process tmp=arr[0];
                tmp.slack=tmp.deadline-tmp.arrival-tmp.burst;
                waiting[cur] = tmp;
                arr.erase(arr.begin());
            }
            deadSort(waiting);
            for(int i=0;i<waiting.size();i++){
                if(waiting[i].slack<0){                    
                    std::cout<<currentTime<<"\t"<<waiting[i].pid<<" failed to complete"<<"\t"<<waiting[i].slack<<"\n";
                    waiting.erase(waiting.begin() + i);
                    completed++;
                    i--;
                    failed++;
                } else {break;}
            }
            waiting[0].burst--;
                if(waiting[0].burst==0){
                    std::cout<<currentTime<<waiting[0].pid<<" completed"<<waiting[0].slack<<"\n";
                    waiting.erase(waiting.begin());
                    arr[completed].completion_time = currentTime;
                    arr[completed].turnaround_time = arr[completed].completion_time - arr[completed].arrival;
                    arr[completed].waiting_time = arr[completed].turnaround_time - arr[completed].burst;
                    total_turnaround_time += arr[completed].turnaround_time;
                    total_waiting_time += arr[completed].waiting_time;
                    completed++;
                    passed++;
                }
            for(int i=0;i<waiting.size();i++){
                waiting[i].slack--;
            }
        }
        currentTime++;
    }


    avg_turnaround_time = total_turnaround_time / arrCount;
    avg_waiting_time = total_waiting_time / arrCount;


    std::cout<<"Total processes completed = "<<passed<<endl;
    std::cout<<"Total processes failed = "<<failed<<endl;
    std::cout<<"Average Turnaround Time = "<<avg_turnaround_time<<endl;
    std::cout<<"Average Waiting Time = "<<avg_waiting_time<<endl;
}




void srt::deadSort(std::vector<process> things){
    if(things.size()>1){
        std::sort(things.begin(),things.end(),[](const process& lhs, const process& rhs){
            return lhs.slack<rhs.slack;
        });
    }
}