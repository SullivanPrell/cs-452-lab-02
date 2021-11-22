#ifndef CS_452_LAB_02_MFQS_H
#define CS_452_LAB_02_MFQS_H

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
#include "Queue.h"
#include <numeric>
using namespace std;


class mfqs{
	public:
		static void doQueues(std::vector<process> v, int arrCount, bool ioMode);
		static void supersort(std::vector<process> v);
		static vector<process> doManuel();
};

#endif //CS_452_LAB_02_MFQS_H
