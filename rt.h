#ifndef CS_452_LAB_02_SRT_S
#define CS_452_LAB_02_SRT_S

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "Queue.h"
#include "process.h"
#include <vector>


class rt{
    public:
        static void dosrt(std::vector<process> arr, int arrCount);
		static void dohrt(std::vector<process> arr, int arrCount);
        static void performHardRealTime(std::vector<process> &processes, int numProcess);
        static void deadSort(std::vector<process> things);
		static void inversion(std::vector<process> things);
};

#endif