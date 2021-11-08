#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
using namespace std;

void mfqs(process raw, int arrCount);



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

void roundRobinProcessing(process arr[], int arrCount, int tq);
void queueUpdationRoundRobin(process arr[], int timer,int arrCount, int maxProccessIndex);
void queueMaintainenceRoundRobin(process arr[], int arrCount);
void srt(process arr[], int arrCount);
void hrt(process arr[], int arrCount);
void display(process proc);
void quickSort(process arr[], int low, int high);
int partition (process arr[], int low, int high);
void swap(process* a, process* b);

int main(int argc, char** argv){
	cout << "Size of a proc: " << sizeof (process)<<"\n";
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
	
	int time=0;
	bool processed;


}

void srt(process arr[], int arrCount){}

void hrt(process arr[], int arrCount){}

void display(process proc){
	cout << proc.pid << " " << proc.burst << " " << proc.arrival << " " << proc.priority << " " << proc.deadline << " " << proc.io << "\n";
}

void queueUpdationRoundRobin(process arr[], int timer,int arrCount, int maxProccessIndex){
    int zeroIndex;
    for(int i = 0; i < arrCount; i++){
        if(arr[i].queue == 0){
            zeroIndex = i;
            break;
        }
    }  
    arr[zeroIndex].queue = maxProccessIndex + 1;
}

void queueMaintainenceRoundRobin(process arr[], int arrCount){
    for(int i = 0; (i < arrCount-1) && (arr[i+1].queue != 0) ; i++){
        int temp = arr[i].queue;
        arr[i].queue = arr[i+1].queue;
        arr[i+1].queue = temp;
    }
}

void checkNewArrivalRoundRobin(int timer, process arr[], int arrCount, int maxProccessIndex){
    if(timer <= arr[arrCount-1].arrival){
       bool newArrival = false;
       for(int j = (maxProccessIndex+1); j < arrCount; j++){
             if(arr[j].arrival <= timer){
              if(maxProccessIndex < j){
                 maxProccessIndex = j;
                 newArrival = true;
              }
           }
       }
       //adds the incoming process to the ready queue
       //(if any arrives)
       if(newArrival)
          queueUpdationRoundRobin(arr,timer,arrCount, maxProccessIndex);
    }
}

void roundRobinProcessing(process arr[], int arrCount, int tq) {
	bool complete[arrCount];
	float avgWait = 0, avgTT = 0;
	int timer = 0, maxProcessIndex = 0;
	int temp_burst[arrCount];
	int turn[arrCount];
	int wait[arrCount];

	for(int i = 0; i < arrCount; i++){
        temp_burst[i] = arr[i].burst;
    }

	for(int i = 0; i < arrCount; i++){    //Initializing the complete array
        complete[i] = false;
    }
    while(timer < arr[0].arrival)    //Incrementing Timer until the first process arrives
        timer++;
    arr[0].queue = 1;
     
    while(true){
        bool flag = true;
        for(int i = 0; i < arrCount; i++){
            if(temp_burst[i] != 0){
                flag = false;
                break;
            }
        }
        if(flag)
            break;
 
        for(int i = 0; (i < arrCount) && (arr[i].queue != 0); i++){
            int ctr = 0;
            while((ctr < tq) && (temp_burst[arr[0].queue-1] > 0)){
                temp_burst[arr[0].queue-1] -= 1;
                timer += 1;
                ctr++;
 
                //Checking and Updating the ready queue until all the processes arrive
                checkNewArrivalRoundRobin(timer, arr, arrCount, maxProcessIndex);
            }
            //If a process is completed then store its exit time
            //and mark it as completed
            if((temp_burst[arr[0].queue-1] == 0) && (complete[arr[0].queue-1] == false)){
                //turn array currently stores the completion time
                turn[arr[0].queue-1] = timer;       
                complete[arr[0].queue-1] = true;
            }
             
              //checks whether or not CPU is idle
            bool idle = true;
            if(arr[arrCount-1].queue == 0){
                for(int i = 0; i < arrCount && arr[i].queue != 0; i++){
                    if(complete[arr[i].queue-1] == false){
                        idle = false;
                    }
                }
            }
            else
                idle = false;
 
            if(idle){
                timer++;
                checkNewArrivalRoundRobin(timer, arr, arrCount, maxProcessIndex);
            }
       
            //Maintaining the entries of processes
            //after each premption in the ready Queue
            queueMaintainenceRoundRobin(arr, arrCount);
        }
    }
 
    for(int i = 0; i < arrCount; i++){
        turn[i] = turn[i] - arr[i].arrival;
        wait[i] = turn[i] - arr[i].burst;
    }
 
    cout << "\nProgram No.\tArrival Time\tBurst Time\tWait Time\tTurnAround Time"
         << endl;
    for(int i = 0; i < arrCount; i++){
        cout<<i+1<<"\t\t"<<arr[i].arrival<<"\t\t"
          <<arr[i].burst<<"\t\t"<<wait[i]<<"\t\t"<<turn[i]<<endl;
    }
    for(int i =0; i< arrCount; i++){
        avgWait += wait[i];
        avgTT += turn[i];
    }
    cout<<"\nAverage wait time : "<<(avgWait/arrCount)
      <<"\nAverage Turn Around Time : "<<(avgTT/arrCount);
 
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