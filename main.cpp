#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
using namespace std;
void mfqs();
void srt();
void hrt();



class process{
	public:
		int pid;
		int burst;
		int arrival;
		int priority;
		int deadline;
		int io;
		int queue;
		process* next;
		process* prev;
		bool head;
		bool tail;
};



void display(process proc);
void quickSort(process arr[], int low, int high);
int partition (process arr[], int low, int high);
void swap(process* a, process* b);

int main(int argc, char** argv){
	cout << "Size of a proc: " << sizeof (process)<<"\n";
	if(argc!=2){
		printf("Incorrect parameter number\n");
		return 0;
	}

	ifstream inputFile {argv[1]};
	ofstream outputFile {"cmd.txt"};

	string line;
	int ProcNum=0;
	while(getline(inputFile,line)){
		if(line.find('-')>line.length()&&line.find('P')>line.length()){
			outputFile << line << "\n";
			ProcNum++;
		}	
		outputFile.flush();
	} 

	//Closing file
	inputFile.close();
	outputFile.close();

	ifstream commands {"cmd.txt"};
	process* arr=new process[ProcNum];
	printf("Arr made\n");

	for(int i=1;i<ProcNum;i++){
		
		line="";
		getline(commands,line);
		stringstream is(line);
		int n;
		is >> n;
		arr[i].pid=n;
		is >> n;
		arr[i].burst=n;
		is >> n;
		arr[i].arrival=n;
		is >> n;
		arr[i].priority=n;
		is >> n;
		arr[i].deadline=n;
		is >> n;
		arr[i].io=n;
	}

	commands.close();

	quickSort(arr,0,ProcNum-1);
	arr[0].next=&arr[1];
	arr[0].tail=false;
	arr[0].head=true;
	for(int i=1;i<ProcNum-1;i++){
		arr[i].next=&arr[i+1];
		arr[i].prev=&arr[i-1];
		arr[i].head=false;
		arr[i].tail=false;
		display(arr[i]);
	}
	arr[ProcNum].prev=&arr[ProcNum-1];
	arr[ProcNum].head=false;
	arr[ProcNum].tail=true;

	bool select=false;
	string mode="";
	while(!select){
		cout<< "Select mfqs, srt, or hrt\n";
		cin>>mode;
		if(mode=="mfqs"){
			mfqs(arr[0]);
			select=true;
		}
		else if(mode=="srt"){
			srt();
			select=true;
		}
		else if(mode=="hrt"){
			hrt();
			select=true;
		}
	}

	cout<< "Terminated Cleanly with "<<ProcNum<<" processes scheduled \n";
    return 0;
}

void mfqs(process raw){
	int queues, quantum, age;

	while(1){	
		cout << "How many queues will be generated\n";
		cin >> queues;
		if(cin.fail()||queues<2||queues>5){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
		}
		else{
			break;
		}
	}
	while(1){
		cout << "What is the time quantum\n";
		cin >> quantum;
		if(cin.fail()||quantum<1){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
		}
		else{
			break;
		}
	}
	while(1){
		cout << "How long should processes take to age up\n";
		cin >> age;
		if(cin.fail()||age<1){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
		}
		else{
			break;
		}
	}
	
	int time=0;
	bool processed;


}

void srt(){}

void hrt(){}

void display(process proc){
	cout << proc.pid << " " << proc.burst << " " << proc.arrival << " " << proc.priority << " " << proc.deadline << " " << proc.io << "\n";
}

void swap(process* a, process* b){
    process t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (process arr[], int low, int high){
    int pivot = arr[high].arrival;    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++){
        // If current element is smaller than or
        // equal to pivot
        if (arr[j].arrival <= pivot)
        {
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
void quickSort(process arr[], int low, int high){
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}