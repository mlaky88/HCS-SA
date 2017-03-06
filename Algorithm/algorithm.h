#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

#include "../Individual/individual.h"

class Algorithm
{
protected :
    int NP,D, seed, FEs, MAXFEs, runs, funcNum, G;
    rand_t rnd;

public:
    Algorithm(int NP,int D,int seed, int runs, int func_num);
    void settings();
    std::string name;
    virtual void runExperiment();
    std::ofstream file;

    std::vector<int> functions;
    std::vector<int> seeds;
    std::vector<std::string> funName;


};

#endif // ALGORITHM_H
