
#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#define MIN -100
#define MAX  100
#include <iostream>
#include <random>
#include "../BenchmarkCEC2014/benchmarkcec2014.h"

typedef std::mt19937 rand_t;

class Individual
{
protected:

    double eval;
    int D;
    std::vector<double> x;

public:
    Individual(int D);
    bool operator==(Individual &obj);

    void generateIndividual(rand_t &rnd);
    void evaluate(int funcNum);
    inline double getEval() const {return eval;}

    void toString();

    inline double getX(int position) {return x[position]; }
    inline double setX(int position, double value) {x[position] = value; }
    inline std::vector <double> getX() const { return x; }
    inline void setX(std::vector<double> x) { this->x = x; }
    inline void setEval(double eval) { this->eval = eval; }

    void clear();
    void repair(rand_t &rnd);
    void repairWithParent(Individual parent);

    double distance(const Individual x);

    BenchmarkCec2014* function;

};

#endif // INDIVIDUAL_H
