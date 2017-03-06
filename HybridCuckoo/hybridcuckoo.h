#ifndef HYBRIDCUCKOO_H
#define HYBRIDCUCKOO_H

#include "../Individual/CIndividual.h"
#include "../Algorithm/algorithm.h"


class HybridCuckoo :public Algorithm
{
private:
    std::vector<Cindividual> pop;
    std::vector<Cindividual> trialPop;

    void abandon_nests(Cindividual &trial);
    int findBestPosition();
    int findDefiniteBest();
    void generate_new_solution(Cindividual& trial, int current, int pbest);
    void generate_new_solution(Cindividual& trial, int current);
    void generatePopulation();
    void printResults(int run);
    void generate_trial_pop(Cindividual &trial, int funcNum);
    bool reduce_pop();
    std::mt19937 rnd;

    double pa, pb, pc, p_best_rate;
    int p_num, max_pop_size;

public:
    HybridCuckoo(int NP, int D, int seed, int runs, int funcNum, double p_c, double p_b, double p_a);
    void run();
    void runExperiment();

};

#endif // HYBRIDCUCKOO_H
