#include "hybridcuckoo.h"
#include <chrono>

HybridCuckoo::HybridCuckoo(int NP, int D, int seed, int runs, int funNum, double p_c, double p_b, double p_a) : Algorithm(NP,D,seed,runs,funNum)
{
    FEs = 0;
    p_best_rate = 0.05;
    p_num = round(NP *  p_best_rate);
    max_pop_size = NP;
    this->pc =p_c;
    this->pb = p_b;
    this->pa = p_a;
}
void HybridCuckoo::runExperiment()
{
    std::vector<int>::iterator s = seeds.begin();
    for(int f : functions) {
        this->funcNum = f;
        s=seeds.begin();
        for (int i = 0; i < runs; i++){
            srand(*s);
            rnd.seed(*s);
            generatePopulation();
            run();
            printResults(i);
            ++s;
        }

    }
}
void HybridCuckoo::generatePopulation()
{
    NP = max_pop_size;
    Cindividual ind(D);
    pop.clear();
    for(int i = 0; i < NP; i++){
        ind.generateIndividual(rnd);
        ind.evaluate(funcNum);
        pop.push_back(ind);
        ind.clear();
    }
    FEs = NP;

}

void HybridCuckoo::generate_new_solution(Cindividual& trial, int current,int pbest)
{
    trial.clear();
    double tao = 0.10;
    static std::uniform_real_distribution<double> randDist(0,1);
    double random = randDist(rnd);
    if(random < pb) { //exploitation

        if(randDist(rnd) < tao) trial.setAlphaLocal(randDist(rnd));
        else trial.setAlphaLocal(pop[current].get_aL());
	
        if(randDist(rnd) < tao) trial.setCr(randDist(rnd));
        else trial.setCr(pop[current].getCr());

        trial.setAlphaLevy(pop[current].get_aLevy());
        trial.setAlphaGlobal(pop[current].get_aG());

        unsigned int r1, r2, r3;
        do{ r1 = randDist(rnd) * NP; } while(r1 == current);
        do{ r2 = randDist(rnd) * NP; } while(r1 == r2 || r2 == current);
        do{ r3 = randDist(rnd) * NP; } while(r1 == r2 || r2 == r3 || r3 == current);

        int jrand = D*randDist(rnd);
        for(int j = 0; j < D; j++) {
            if(randDist(rnd) < trial.getCr() || j == jrand)
                trial.setX(j, pop[current].getX(j) + trial.get_aL() * (pop[pbest].getX(j)-pop[current].getX(j)) + trial.get_aL() * (pop[r1].getX(j)-pop[r2].getX(j)));
            else
                trial.setX(j,pop[current].getX(j));
        }
    }
    else {// exploration

        if(randDist(rnd) < tao) trial.setAlphaGlobal(randDist(rnd));
        else trial.setAlphaGlobal(pop[current].get_aG());

        if(randDist(rnd) < tao) trial.setAlphaLevy(1.2 + randDist(rnd) * 0.6);
        else trial.setAlphaLevy(pop[current].get_aLevy());

        trial.setAlphaLocal(pop[current].get_aL());
        trial.setCr(pop[current].getCr());
        for(int j = 0; j < D; j++) {
            if(randDist(rnd) < pa) trial.setX(j,pop[pbest].getX(j) + trial.get_aG() * Cindividual::levyWalk(1,trial.get_aLevy(),rnd));
            else trial.setX(j,pop[current].getX(j) + trial.get_aG() * Cindividual::levyWalk(1,trial.get_aLevy(),rnd));
        }
    }
    trial.repairWithParent(pop[current]);
}


//GENERATE TRIALPOP BASED ON POPULATION DIVERSITY
void HybridCuckoo::generate_trial_pop(Cindividual& trial, int funNum)
{
        static std::uniform_real_distribution<double> randDist(0,1);
    int j = 0;
    for (int i = 0; i < NP; i++) {
        if(randDist(rnd) < pc) j = findDefiniteBest(); //definite best was before
        else j = i;
        generate_new_solution(trial,j,findBestPosition());
        trial.evaluate(funNum); FEs++;
        if(trial.getEval() < pop[j].getEval()) pop[j] = trial;
    }
}

int HybridCuckoo::findBestPosition()
{
    std::vector<int> idx(NP);
    for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;
    std::sort(idx.begin(), idx.end(), [this](size_t i1, size_t i2) {return pop[i1].getEval() < pop[i2].getEval();});
    int index = rand() % p_num;
    return idx[index];
}

int HybridCuckoo::findDefiniteBest()
{
    auto best = std::min_element(pop.begin(),pop.end(),[](Cindividual& lhs, Cindividual& rhs){return lhs.getEval() < rhs.getEval();});
    return std::distance(pop.begin(),best);
}


void HybridCuckoo::abandon_nests(Cindividual& trial)
{
        static std::uniform_real_distribution<double> randDist(0,1);
    for (int i = 0; i < NP; i++) {
        if(randDist(rnd) < pa) {
            auto worst = std::max_element(pop.begin(),pop.end(),[](const Cindividual& lhs, const Cindividual& rhs){return lhs.getEval() < rhs.getEval();});
            trial.generateIndividual(rnd);
            trial.evaluate(funcNum); FEs++;
            if(trial.getEval() < worst->getEval()) {
                *worst = trial;
            }
        }
    }
}

void HybridCuckoo::run()
{
    Cindividual trial(D);
    while(FEs < MAXFEs) {
        generate_trial_pop(trial,funcNum);
        if(!reduce_pop())
            abandon_nests(trial);
    }
    std::sort(pop.begin(),pop.end(),[](const Cindividual& lhs, const Cindividual& rhs){return lhs.getEval() < rhs.getEval();});
}

bool HybridCuckoo::reduce_pop()
{
    int min_pop_size = 10; //Set to 10 to maintain a higher diversity towards the end of evolution

    int plan_pop_size = round((((min_pop_size - max_pop_size) / (double)MAXFEs) * FEs) + max_pop_size);
    if (NP > plan_pop_size) {
        int reduction_ind_num = NP - plan_pop_size;
        if (NP - reduction_ind_num <  min_pop_size) reduction_ind_num = NP - min_pop_size;
        for (int i = 0; i < reduction_ind_num; i++) {
            int worst_ind = 0;
            for (int j = 1; j < NP; j++) {
              if (pop[j].getEval() > pop[worst_ind].getEval()) worst_ind = j;
            }
            pop.erase(pop.begin() + worst_ind);
            NP--;
        }
        p_num = round(NP *  p_best_rate);
            if (p_num <= 1)  p_num = 2;

        return true;
    }
    return false;
}

void HybridCuckoo::printResults(int i)
{
    std::cout<<"F"<< funcNum<<"("<<D<< "D), run = "<< i+1 <<", e = "<<pop[0].getEval() << std::endl;
}

