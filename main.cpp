#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "Queue.h"
#include "process.h"
#include <vector>
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

void mfqs(Queue raw, int arrCount);

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

void supersort(vector<process> prioritySort);

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
	
    inputFile.close();

    process *arr = new process[ProcNum];

    for (int i = 0; i < ProcNum; i++) {
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
		arr[i].age=0;
    }



	quickSort(arr,0,ProcNum-1);

	
    bool select = false;
    string mode = "mfqs";
    while (!select) {
        //cout << "Select mfqs, srt, or hrt\n";
        //cin >> mode;
        if (mode == "mfqs") {
			Queue prime;
			for(int i=0;i<ProcNum;i++){
				prime.enQueue(arr[i]);
			}
            mfqs(prime, ProcNum);
            select = true;
        } else if (mode == "srt") {
            srt(arr[0], ProcNum);
            select = true;
        } else if (mode == "hrt") {
            hrt(arr[0], ProcNum);
            select = true;
        }
    }
	
    //cout << "Terminated Cleanly with " << ProcNum << " processes scheduled \n";
    return 0;
}

void mfqs(Queue prime, int arrCount) {
    int queues=5;
	int quantum=4; 
	int age=500;
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
	
	Queue things[queues];
	int clocktick=0;
	int workDone=0;
	int i=0;
	int context=-1;
	int procDone=0;
	int queued=0;
	int modQuantum;
	printf("We have %d procs\n",arrCount);
	vector<process> prioritySort;

	while(1){
		//checks to see if everything is queued. if not it adds all items that have arrived
		//at the current clock tick
		
		/*if(queued<arrCount){
			while(queued<arrCount&&prime.peekQueue().arrival==clocktick){
				process tmp=prime.popQueue();
				things[0].enQueue(tmp);
				queued++;
			}
		}*/

		if(queued<arrCount){
			while(queued<arrCount&&prime.peekQueue().arrival==clocktick){
				process tmp=prime.popQueue();
				queued++;
				prioritySort.push_back(tmp);
			}
			supersort(prioritySort);
			if(prioritySort.size()>0){
				for(int a=0;a<prioritySort.size();a++){
					things[0].enQueue(prioritySort.at(a));
				}
			}
			prioritySort.clear();
		}


		//determines the first queue to have contents
		for(i=0;i<queues;i++){
			if(things[i].checkReal()){
				break;
			}
		}

		//checks to make sure we are in valid queues. 
		//The only time this is relevant is if all queues are empty
		
		if(i==queues){
			clocktick++;
			continue;
		}
		
		//checks to see if current queue is the same as last loop. 
		//if not it resets the timer for demotions
		if(context!=i){
			//workDone=0;
			context=i;
			modQuantum=quantum*pow(2,i);
		}

		things[i].deincrement();
		things[i].doWork();
		//workDone++;

		if(things[i].peekQueue().burst==0){
			process tmp=things[i].popQueue();
			procDone++;
			//workDone=0;
			printf("Process %d terminated in queue %d\n",tmp.pid,i+1);
			
		}
		else if(things[i].peekQueue().worked==modQuantum&&i<queues-2){
			process tmp=things[i].popQueue();
			tmp.worked=0;
			things[i+1].enQueue(tmp);
		}
		else if(things[i].peekQueue().worked==modQuantum&&i==queues-2){
			process tmp=things[i].popQueue();
			tmp.worked=0;
			prioritySort.push_back(tmp);
		}

		things[queues-1].ageQueue();
		
		while(things[queues-1].checkReal()&&things[queues-1].peekQueue().age==age){
			process tmp=things[queues-1].popQueue();
			tmp.age=0;
			prioritySort.push_back(tmp);
		}

		supersort(prioritySort);
		if(prioritySort.size()>0){
			for(int a=0;a<prioritySort.size();a++){
				things[queues-2].enQueue(prioritySort.at(a));
			}
			prioritySort.clear();
		}
		clocktick++;
		if(procDone==arrCount){
			break;
		}
	}
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

void supersort(vector<process> prioritySort){
	if(prioritySort.size()>1){		
		sort(prioritySort.begin(),prioritySort.end(),[](const process& lhs, const process& rhs){
			return lhs.priority<rhs.priority;
		});
	}
}