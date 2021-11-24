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
vector<process> doManuel();

int main(int argc, char **argv) {
	vector<process> processes;
	int numProcess;
	string mode;
	bool ioMode=false;
    if (argc > 2) {
        printf("Incorrect parameter number\n");
        return 0;
    }
	else if(argc==1){
		cout << "Select mfqs, srt, hrt\n";
		cin >> mode;
		string dump;
		processes=doManuel();
		numProcess=processes.size();
	}
	else{
		string io;
		cout << "Select mfqs, srt, hrt\n";
		cin >> mode;
		string dump;
		if(mode=="mfqs"){
			cout<<"Would you like to do i/o? Press 1 for yes, any other key for no\n";
			cin>>io;
		}
		ifstream fileIn{argv[1]};
		processes;
		numProcess = 0;
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
				if (tempProcess.pid < 0 || tempProcess.burst < 1 || tempProcess.arrival < 0 || tempProcess.deadline < 0 ||tempProcess.io < 0 || tempProcess.priority < 0) {
					//ignore
				} else if(io=="1"&&tempProcess.burst<=tempProcess.io&&tempProcess.io>0){
					//ignore
				}
				else {
					tempProcess.age = 0;
					tempProcess.queue = 0;
					tempProcess.worked = 0;
					processes.push_back(tempProcess);
					numProcess++;
				}
				if(io=="1"){
					ioMode=true;
				}
			}
		}
		fileIn.close();
	}
    bool select = false;

    while (!select) {
        if (mode == "mfqs") {
            mfqs::doQueues(processes, numProcess,ioMode);
            select = true;
        } else if (mode == "srt") {
            int time;
            cout << "Starting soft real time scheduling:\n";
            rt::dosrt(processes, numProcess);
            select = true;

        } else if (mode == "hrt") {
            rt::dohrt(processes, numProcess);
            select = true;
        }else{
			cout<<"Bad input, please select mfqs, srt, or hrt\n";
			cin >> mode;
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



vector<process> doManuel(){
	bool fin=false;
	vector<process> processes;
	int input;
	while(!fin){
		process tmp;
		cout<<"Pid?\n";
		cin>>input;
		if(cin.fail()){
			cin.clear();
			printf("Invalid input, please restart current process input\n");
			continue;
		}
		tmp.pid = input;
		cout<<"Burst?\n";
		cin>>input;
		if(cin.fail()){
			cin.clear();
			printf("Invalid input, please restart current process input\n");
			continue;
		}
		tmp.burst = input;
		cout<<"Arrival?\n";
		cin>>input;
		if(cin.fail()){
			cin.clear();
			printf("Invalid input, please restart current process input\n");
			continue;
		}
		tmp.arrival = input;
		cout<<"Priority?\n";
		cin>>input;
		if(cin.fail()){
			cin.clear();
			printf("Invalid input, please restart current process input\n");
			continue;
		}
		tmp.priority = input;
		cout<<"Deadline?\n";
		cin>>input;
		if(cin.fail()){
			cin.clear();
			printf("Invalid input, please restart current process input\n");
			continue;
		}
		tmp.deadline = input;
		cout<<"IO?\n";
		cin>>input;
		if(cin.fail()){
			cin.clear();
			printf("Invalid input, please restart current process input\n");
			continue;
		}
		tmp.io = input;
		tmp.age = 0;
		tmp.queue = 0;
		tmp.worked = 0;
		tmp.trueBurst = tmp.burst;
		if (tmp.pid < 0 || tmp.burst < 0 || tmp.arrival < 0 || tmp.deadline < 0 ||
			tmp.io < 0 || tmp.priority < 0) {
			//ignore
		} else {
			tmp.age = 0;
			tmp.queue = 0;
			tmp.worked = 0;
			processes.push_back(tmp);
		}
		while(1){
			cout<<"Woud you like to enter another process? Press 1 for yes, 2 for no\n";
			cin>>input;
			if(cin.fail()){
				cin.clear();
				printf("That is not valid input\n");
			}
			else if(input==1){
				break;
			}else if(input==2){
				fin=true;
				break;
			}
			else{
				cin.clear();
				printf("That is not valid input\n");
			}
		}
	}
	return processes;
}