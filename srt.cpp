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
        } 
		else {
			if(arr.size()==0){
				break;
			}
            int cur = 0;
            while ( (arr.size()>0) && (arr.at(0).arrival==currentTime) ){
                process tmp=arr.at(0);
                waiting.push_back(tmp);
                arr.erase(arr.begin());
            }
			if(waiting.size()>0){
				deadSort(waiting);
				while(1){
					if(waiting.size()==0){
						break;
					}
					if(waiting.at(0).deadline-waiting.at(0).burst<currentTime){                    
						std::cout<<currentTime<<"\t"<<waiting.at(0).pid<<" failed to complete\n";
						waiting.erase(waiting.begin());
						completed++;
						failed++;
					} 
					else {
						break;
					}
				}
				if(waiting.size()==0){
					currentTime++;
					continue;
				}
				waiting.at(0).burst--;
				if(waiting.at(0).burst<=0){
					std::cout<<waiting.at(0).pid<<" completed\n";
					process tmp=waiting.at(0);
					waiting.erase(waiting.begin());
					tmp.completion_time = currentTime;
					tmp.turnaround_time = tmp.completion_time - tmp.arrival;
					tmp.waiting_time = tmp.turnaround_time - tmp.burst;
					total_turnaround_time += tmp.turnaround_time;
					total_waiting_time += tmp.waiting_time;
					completed++;
					passed++;
				}
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
            return lhs.deadline<rhs.deadline;
        });
    }
}