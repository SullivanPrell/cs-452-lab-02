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


class srt{
    public:
    static void dosrt(std::vector<process> arr, int arrCount, int quantum);
    static void deadSort(vector<process> things);
};

#endif