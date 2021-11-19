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
	bool add=false;
	int max;
	

	std::sort(arr.begin(),arr.end(),[](const process& lhs, const process& rhs){
		return lhs.arrival>rhs.arrival;
	});
    while (ProcsCompleted == false) {
        if (completed == arrCount) {
            ProcsCompleted = true;
        } 
		else {
			if(arr.size()>0){
				int top=arr.size()-1;
				while (arr.size()>0&&arr[top].arrival==currentTime){
					process tmp=arr[top];
					waiting.push_back(tmp);
					arr.erase(arr.end()-1);
					top--;
					add=true;
				}
			}
			max=waiting.size()-1;

			if(add){
				std::sort(waiting.begin(),waiting.end(),[](const process& lhs, const process& rhs){
					return lhs.deadline>rhs.deadline;
				});
				add=false;
			}
			if(waiting.size()>0){
				while(1){
					if(waiting.size()==0){
						break;
					}
					if(waiting[max].deadline<waiting[max].burst+currentTime){                    
						//std::cout<<currentTime<<"\t"<<waiting.at(max).pid<<" failed to complete\n";
						process tmp=waiting[max];
						waiting.erase(waiting.end()-1);
						max--;
						completed++;
						failed++;
						tmp.completion_time = currentTime;
						tmp.turnaround_time = tmp.completion_time - tmp.arrival;
						if(tmp.turnaround_time>tmp.trueBurst){
							tmp.waiting_time = tmp.turnaround_time - tmp.trueBurst;
						}
						else{
							tmp.waiting_time=0;
						}
						total_turnaround_time += tmp.turnaround_time;
						total_waiting_time += tmp.waiting_time;
					} 
					else {
						break;
					}
				}
				if(waiting.size()==0){
					currentTime++;
					continue;
				}
				waiting[max].burst--;
				if(waiting[max].burst==0){
					//std::cout<<currentTime<<"\t"<<waiting[max].pid<<" completed\n";
					process tmp=waiting[max];
					waiting.erase(waiting.end()-1);
					max--;
					completed++;
					passed++;
					//cout << tmp.pid << " " << tmp.burst << " " << tmp.arrival << " " << tmp.priority << " " << tmp.deadline << " "<< tmp.io << "\n";
					tmp.completion_time = currentTime;
					tmp.turnaround_time = tmp.completion_time - tmp.arrival;
					tmp.waiting_time = tmp.turnaround_time - tmp.trueBurst;
					total_turnaround_time += tmp.turnaround_time;
					total_waiting_time += tmp.waiting_time;
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
            return lhs.deadline>rhs.deadline;
        });
    }
}

void srt::inversion(std::vector<process> things){
    if(things.size()>1){
        std::sort(things.begin(),things.end(),[](const process& lhs, const process& rhs){
            return lhs.arrival>rhs.arrival;
        });
    }

}