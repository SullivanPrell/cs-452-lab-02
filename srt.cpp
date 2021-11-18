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


    std::cout<<"#P\t"<<"AT\t"<<"BT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;

    while (ProcsCompleted == false) {
        if (completed == arrCount) {
            ProcsCompleted = true;
        } else {
            int cur = 0;
            while ( (arr.size()>0) && (arr.at(cur).arrival==currentTime) ){
                process tmp=arr.at(cur);
                tmp.slack=tmp.deadline-(tmp.burst-currentTime);
                waiting.push_back(tmp);
                arr.erase(arr.begin());
            }
            deadSort(waiting);
            for(int i=0;i<waiting.size();i++){
                if(waiting.at(i).slack<0){
                    std::cout<<waiting.at(i).pid<<" failed to complete"<<waiting.at(i).slack<<"\n";
                    waiting.erase(waiting.begin() + i);
                    completed++;
                    i--;
                } else {break;}
            }
            waiting.at(0).burst--;
                if(waiting.at(0).burst==0){
                    std::cout<<waiting.at(0).pid<<" completed\n";
                    waiting.erase(waiting.begin());
                    arr[completed].completion_time = currentTime;
                    arr[completed].turnaround_time = arr[completed].completion_time - arr[completed].arrival;
                    arr[completed].waiting_time = arr[completed].turnaround_time - arr[completed].burst;
                    total_turnaround_time += arr[completed].turnaround_time;
                    total_waiting_time += arr[completed].waiting_time;
                    completed++;
                }
            for(int i=0;i<waiting.size();i++){
                waiting.at(i).slack--;
            }
        }
        currentTime++;
    }


    avg_turnaround_time = total_turnaround_time / arrCount;
    avg_waiting_time = total_waiting_time / arrCount;

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