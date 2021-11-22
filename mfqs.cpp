#include "mfqs.h"


void mfqs::doQueues(std::vector<process> processes, int arrCount, bool io) {
    int queues = 5;
    int quantum = 4;
    int age = 50;

	Queue prime;
	sort(processes.begin(), processes.end(), [](const process &lhs, const process &rhs) {
		return lhs.arrival < rhs.arrival;
	});
	for (int i = 0; i < arrCount; i++) {
		prime.enQueue(processes[i]);
	}
    
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
	}
    
    Queue things[queues];
    int clocktick = 0;
    int workDone =0;
    int i = 0;
    int context = -1;
    int procDone = 0;
    int queued = 0;
    int modQuantum;
    printf("We have %d procs\n", arrCount);
    vector<process> ioVector[queues + 1];
	vector<string> outputVector;
	string output;
	vector<int> aveWait;
	vector<int> aveTurn;
	int inQueue=0;
    while (1) {
        //checks to see if everything is queued. if not it adds all items that have arrived
        //at the current clock tick
		outputVector.push_back("At "+std::to_string(clocktick)+": ");

        while (queued < arrCount && prime.peekQueue().arrival == clocktick) {
            process tmp = prime.popQueue();
            queued++;
            ioVector[0].push_back(tmp);
        }

        //determines the first queue to have contents
        for (i = 0; i < queues; i++) {
            if (things[i].checkReal()) {
                break;
            }
        }

        modQuantum = quantum * pow(2, i);
        if (i < queues) {
            things[i].deincrement();
            things[i].doWork();
            if (things[i].peekQueue().burst == 0) {
                process tmp = things[i].popQueue();
                procDone++;
				int num=clocktick-tmp.arrival;
				aveTurn.push_back(num);
				aveWait.push_back(num-tmp.trueBurst);
                
				//printf("Process %d terminated in queue %d\n", tmp.pid, i + 1);
				outputVector.push_back("Process "+to_string(tmp.pid)+" terminated in queue "+to_string(i+1));
            } 
			else if (things[i].peekQueue().burst == 1&&things[i].peekQueue().io>0&&io) {
                process tmp = things[i].popQueue();
                tmp.queue = 0;
                ioVector[queues].push_back(tmp);
				//printf("Process %d sent to io\n", tmp.pid);
				outputVector.push_back("Process "+std::to_string(tmp.pid)+" entered IO");

            }
			else if (things[i].peekQueue().worked >= modQuantum && i < queues - 1) {
                process tmp = things[i].popQueue();
                tmp.worked = 0;
                tmp.queue = i + 1;
                ioVector[tmp.queue].push_back(tmp);
				//printf("Process %d demoted to queue %d\n", tmp.pid, tmp.queue+1);
				outputVector.push_back("Process "+std::to_string(tmp.pid)+" demoted to queue "+std::to_string(tmp.queue+1));
			}
        }

		things[queues - 1].ageQueue();
		while (things[queues - 1].checkReal() && things[queues - 1].peekQueue().age >= age) {
			process tmp = things[queues - 1].popQueue();
			tmp.age = 0;
			ioVector[0].push_back(tmp);
			//printf("Process %d aged up\n", tmp.pid);
			outputVector.push_back("Process "+std::to_string(tmp.pid)+" aged up to queue 1");

		}
        for (int a = 0; a < ioVector[queues].size(); a++) {
            ioVector[queues].at(a).io--;
            if (ioVector[queues].at(a).io <= 0) {
                process tmp = ioVector[queues].at(a);
                ioVector[queues].erase(ioVector[queues].begin() + a);
                a--;
                ioVector[0].push_back(tmp);
            }
        }
        for (int q = 0; q < queues; q++) {
            supersort(ioVector[q]);
            for (int a = 0; a < ioVector[q].size(); a++) {
                things[q].enQueue(ioVector[q].at(a));
            }
            ioVector[q].clear();
        }

		if(outputVector.size()<=1){
			outputVector.clear();
		}
		else{
			if(arrCount<100){
				cout<<outputVector.at(0);
				for(int a=1;a<outputVector.size()-1;a++){
					cout<<outputVector.at(a)<<", ";
				}
				cout<<outputVector.at(outputVector.size()-1)<<"\n";
			}
			else{
				if(clocktick%10000==0){
					printf("%d/%d processes completed\n",procDone,arrCount);
				}
			}
			outputVector.clear();
		}
	
        clocktick++;
        if (procDone == arrCount) {
            break;
        }
    }
	long averageWait = std::accumulate(aveWait.begin(),aveWait.end(),(long)0)/arrCount;
	long averageTurnaround = std::accumulate(aveTurn.begin(),aveTurn.end(),(long)0)/arrCount;
	cout<< "Average Wait time was  \t"<< std::to_string(averageWait)<<" Ticks\n";
	cout<< "Average Turnaround was \t"<<std::to_string(averageTurnaround)<<" Ticks\n";
}
void mfqs::supersort(vector<process> prioritySort){
	if(prioritySort.size()>1){		
		sort(prioritySort.begin(),prioritySort.end(),[](const process& lhs, const process& rhs){
			return lhs.priority<rhs.priority;
		});
	}
}