#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
using namespace std;



class process{
	public:
		int pid;
		int burst;
		int arrival;
		int priority;
		int deadline;
		int io;
		int queue;
		bool head;
		bool tail;
		process* next;
		process* prev;
};



void mfqs(process raw, int arrCount);
void findWaitingTimeRoundRobin(process arr, int arrCount, int wt[], int quantum);
void findTurnAroundTimeRoundRobin(process arr, int arrCount, int wt[], int tat[]);
void findavgTimeRoundRobin(process arr, int arrCount, int quantum);
process findTail(process head);


void srt(process arr[], int arrCount);
void hrt(process arr[], int arrCount);
void display(process proc);
void quickSort(process arr[], int low, int high);
int partition (process arr[], int low, int high);
void swap(process* a, process* b);

int main(int argc, char** argv){
	int arrCount = 0;
	
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
		arrCount++;
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
	}
	arr[ProcNum-1].prev=&arr[ProcNum-2];
	arr[ProcNum-1].head=false;
	arr[ProcNum-1].tail=true;

	display(findTail(arr[0]));

	bool select=false;
	string mode="";
	while(!select){
		cout<< "Select mfqs, srt, or hrt\n";
		cin>>mode;
		if(mode=="mfqs"){
			mfqs(arr[0], arrCount);
			select=true;
		}
		else if(mode=="srt"){
			srt(arr, arrCount);
			select=true;
		}
		else if(mode=="hrt"){
			hrt(arr, arrCount);
			select=true;
		}
	}

	cout<< "Terminated Cleanly with "<<ProcNum<<" processes scheduled \n";
    return 0;
}

void mfqs(process raw, int arrCount){
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
	process* heads = new process[queues];
	for(int i=0;i<queues-1;i++){
		
	
	}


}

void srt(process arr[], int arrCount){}

void hrt(process arr[], int arrCount){}

void display(process proc){
	cout << proc.pid << " " << proc.burst << " " << proc.arrival << " " << proc.priority << " " << proc.deadline << " " << proc.io <<" Head - "<<proc.head <<" | Tail - "<<proc.tail << "\n";
}

void swap(process* a, process* b){
    process t = *a;
    *a = *b;
    *b = t;
}

process findTail(process head){
	while(!head.tail){
		display(head);
		head=*head.next;
	}
	return head;
}

void findWaitingTimeRoundRobin(process arr, int arrCount, int wt[], int quantum)
{
    // Make a copy of burst times bt[] to store remaining
    // burst times.

    int* rem_bt = new int[arrCount];
    for (int i = 0 ; i < arrCount ; i++)
        rem_bt[i] = arr.burst;
		arr = *arr.next;
 
    int t = 0; // Current time
 
    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1)
    {
        bool done = true;
 
        // Traverse all processes one by one repeatedly
        for (int i = 0 ; i < arrCount; i++)
        {
            // If burst time of a process is greater than 0
            // then only need to process further
            if (rem_bt[i] > 0)
            {
                done = false; // There is a pending process
 
                if (rem_bt[i] > quantum)
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t += quantum;
 
                    // Decrease the burst_time of current process
                    // by quantum
                    rem_bt[i] -= quantum;
                }
 
                // If burst time is smaller than or equal to
                // quantum. Last cycle for this process
                else
                {
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
			arr = *arr.next;
        }
 
        // If all processes are done
        if (done == true)
        break;
    }
}

// Function to calculate turn around time
void findTurnAroundTimeRoundRobin(process arr, int arrCount, int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < arrCount ; i++)
        tat[i] = arr.burst + wt[i];
		arr = *arr.next;
}

void findavgTimeRoundRobin(process arr, int arrCount, int quantum)
{
    int* wt = new int[arrCount];
	int* tat = new int[arrCount];
	int total_wt = 0, total_tat = 0;
 
    // Function to find waiting time of all processes
    findWaitingTimeRoundRobin(arr, arrCount, wt, quantum);
 
    // Function to find turn around time for all processes
    findTurnAroundTimeRoundRobin(arr, arrCount, wt, tat);
 
    // Display processes along with all details
    cout << "Processes "<< " Burst time "
        << " Waiting time " << " Turn around time\n";
 
    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<arrCount; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << arr.burst <<"\t "
            << wt[i] <<"\t\t " << tat[i] <<endl;
		arr = *arr.next;
    }
 
    cout << "Average waiting time = "
        << (float)total_wt / (float)arrCount;
    cout << "\nAverage turn around time = "
        << (float)total_tat / (float)arrCount;
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