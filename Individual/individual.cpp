#include "individual.h"

Individual::Individual(int D)
{
    this->D = D;
    x.clear();
    x.resize(D,0);
    function = new BenchmarkCec2014(D);
}

void Individual::generateIndividual(rand_t& rnd)
{
    static std::uniform_real_distribution<double> randDist(0,1);
    x.resize(D,0);
    for (int i=0; i < D;i++) {
        setX(i,((MAX - MIN) * randDist(rnd)) + MIN);
    }
}

void Individual::repair(rand_t & rnd)
{
    static std::uniform_real_distribution<double> uniform01(0,1);
    static std::uniform_real_distribution<double> dis(MIN,MAX);
    for (int i=0; i<D;i++) {
        if(getX(i) < MIN) {
            if(uniform01(rnd) < 0.5)  setX(i, dis(rnd));//MIN);
            else setX(i, MIN +(MIN - getX(i)));
        }
        else if (getX(i) > MAX){
            if(uniform01(rnd) < 0.5) setX(i, dis(rnd));
            else setX(i, MAX-(getX(i) - MAX));
        }
    }
}

void Individual::repairWithParent(Individual parent)
{
    for (int i = 0; i < D; i++) {
        if(getX(i) < MIN) {
            setX(i,(MIN+parent.getX(i))/2.0);
        }
        else if (getX(i) > MAX){
            setX(i,(MAX+parent.getX(i))/2.0);
        }
    }
}


void Individual::clear()
{
    x.clear();
    x.resize(D,0);
    eval = std::numeric_limits<double>::max();
}

void Individual::toString()
{
    std::cout<<"[ ";
    for(int i = 0;i<D;i++){
        if(i == (D-1))
            std::cout << x[i] << " ";
        else
            std::cout << x[i] << ", ";

    }
    std::cout << "] => e = " << eval << std::endl;
}

void Individual::evaluate(int funcNum)
{
    function->cec14_test_func(&x[0],&eval,funcNum);

    eval = eval-function->getfOpt(funcNum);
    eval = eval <= 1e-8 ? 0.0 : eval;
}
double Individual::distance(const Individual ind)
{
    double sum = 0;
    for(unsigned int i=0; i< D; i++)
        sum += (x[i]-ind.x[i]) * (x[i]-ind.x[i]);
    return sqrt(sum);
}
bool Individual::operator ==(Individual& obj)
{
    for(int i = 0; i < D; i++) {
        if(getX(i) != obj.getX(i))
            return false;
    }
    return true;
}
