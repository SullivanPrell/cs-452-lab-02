//
// Created by sulli on 11/14/2021.
//

#ifndef CS_452_LAB_02_HRT_H
#define CS_452_LAB_02_HRT_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "Queue.h"
#include "process.h"
#include <vector>

class hrt {
public:
    static void performHardRealTime(std::vector<process> processes, int numProcess);
};


#endif //CS_452_LAB_02_HRT_H
