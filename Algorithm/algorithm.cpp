#include "algorithm.h"

Algorithm::Algorithm(int NP, int D, int seed, int runs, int func_num)
{
    funName.resize(30,"");
    funName[0] = " Rotated High Conditioned Elliptic Function";
    funName[1] = " Rotated Bent Cigar Function";
    funName[2] = " Rotated Discus Function";
    funName[3] = " Shifted and Rotated Rosenbrock’s Function";
    funName[4] = " Shifted and Rotated Ackley’s Function";
    funName[5] = " Shifted and Rotated Weierstrass Function";
    funName[6] = " Shifted and Rotated Griewank’s Function";
    funName[7] = " Shifted Rastrigin’s Function";
    funName[8] = " Shifted and Rotated Rastrigin’s Function";
    funName[9] = " Shifted Schwefel’s Function";
    funName[10] = "Shifted and Rotated Schwefel’s Function";
    funName[11] = "Shifted and Rotated Katsuura Function";
    funName[12] = "Shifted and Rotated HappyCat Function";
    funName[13] = "Shifted and Rotated HGBat Function";
    funName[14] = "Shifted and Rotated Expanded Griewank’s plus Rosenbrock’s Function";
    funName[15] = "Shifted and Rotated ExpandedFunction";
    funName[16] = "Hybrid Function 1 (N=3)";
    funName[17] = "Hybrid Function 2 (N=3)";
    funName[18] = "Hybrid Function 3 (N=4)";
    funName[19] = "Hybrid Function 4 (N=4)";
    funName[20] = "Hybrid Function 5 (N=5)";
    funName[21] = "Hybrid Function 6 (N=5)";
    funName[22] = "Composition Function 1 (N=5)";
    funName[23] = "Composition Function 2 (N=3)";
    funName[24] = "Composition Function 3 (N=3)";
    funName[25] = "Composition Function 4 (N=5)";
    funName[26] = "Composition Function 5 (N=5)";
    funName[27] = "Composition Function 6 (N=5)";
    funName[28] = "Composition Function 7 (N=3)";
    funName[29] = "Composition Function 8 (N=3)";



    std::uniform_int_distribution<int> dis;
    rand_t rnd;
    this->NP = NP;
    this->D = D;
    this->seed = seed;
    this->runs = runs;
    MAXFEs = 10000 * D;

    if(func_num == 0){
        functions.resize(30,0);
        std::generate(functions.begin(),functions.end(),[]{static int i{1}; return i++;});
    } else {
        seeds.push_back(seed);
        functions.push_back(func_num);
    }
    seeds.resize(runs,0);
    std::for_each (seeds.begin()+1,seeds.end(),[&rnd,&dis](int &seed){seed = dis(rnd);/*rnd.seed(seed);*/});

}
void Algorithm::runExperiment()
{
    std::cout<<"Not yet implemented"<<std::endl;
}

void Algorithm::settings()
{
    std::transform(name.begin(), name.end(), name.begin(), toupper);
    std::cout<<"***************************************"<<std::endl;
    std::cout<<"* Settings of the algorithm "<< name <<std::endl;
    std::cout<<"* NP: "<<NP<<std::endl;
    std::cout<<"* D: "<<std::setw(3)<<D<<std::endl;
    std::cout<<"* RUNS:"<<runs<<std::endl;
    std::cout<<"* FUNCTIONS " << (functions.size() == 1 ? funName[functions[0]-1] : "all")<<std::endl;
    std::cout<<"***************************************"<<std::endl;
}




