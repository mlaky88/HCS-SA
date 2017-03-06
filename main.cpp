#include <iostream>
#include "HybridCuckoo/hybridcuckoo.h"
#include <chrono>
void help();

int main(int argc, char* argv[])
{
    std::cout << std::scientific << std::setprecision(8);

    int NP = 20, seed = 42, D = 10, runs = 5, funcNum = 1;
    double p_c = 0.05;
    double p_b = 0.1;
    double p_a = 0.1;

    std::string algorithm = "hybridcuckoo";
    if(std::string(argv[1]) == "--help" || argc == 1) {
        help();
        return 1;
    }else {
        try {
             for (int i=1;i<argc;i+=2){
                if(std::string(argv[i]) == "--NP") {
                    NP = std::stoi(argv[i+1]);
                }
                else  if(std::string(argv[i]) == "--seed") {
                    seed = std::stoi(argv[i+1]);
                }
                else  if(std::string(argv[i]) == "--D") {
                    D = std::stoi(argv[i+1]);
                }
                else  if(std::string(argv[i]) == "--f") {
                    funcNum = std::stoi(argv[i+1]);
                }
                else  if(std::string(argv[i]) == "--runs") {
                    runs = std::stoi(argv[i+1]);
                }
                else if (std::string(argv[i]) == "--algorithm") {
                    algorithm = std::string(argv[i+1]);
                }
                else if(std::string(argv[i]) == "--pa") {
                    p_a = std::stod(argv[i+1]);

                }
                else if(std::string(argv[i]) == "--pc") {
                    p_c = std::stod(argv[i+1]);
                }
                else if(std::string(argv[i]) == "--pb") {
                    p_b = std::stod(argv[i+1]);
                }
                else {
                    std::cout<<"You must specify a parameter"<<std::endl;
                }
            }
        }catch(...) {
                std::cout<<"Wrong input parameter"<<std::endl;
                help();
                return 1;
        }
    }
    Algorithm* runner;
    if(std::string(algorithm) == "hybridcuckoo") {
        runner = new HybridCuckoo(NP,D,seed,runs,funcNum,p_c,p_b,p_a);
    }

    runner->name = algorithm;
    runner->settings();
    runner->runExperiment();
    return 0;
}

void help()
{
    std::cout << "# Help for using this program" << std::endl;
    std::cout << "# Run as ./HCS-SA --help for this help" << std::endl;
    std::cout << "# Additional parameters are: " << std::endl;
    std::cout << "# --NP ... number of solutions" << std::endl;
    std::cout << "# --D ... dimension of the problem" << std::endl;
    std::cout << "# --seed ... random generator seed" << std::endl;
    std::cout << "# --f ... function number of the CEC14 suite (0 for all functions)" << std::endl;
    std::cout << "# --runs ... number of independent runs" << std::endl;
    std::cout << "# --algorithm ... if more algorithms are implemented specify which " << std::endl;
    std::cout << "# --pa ... reset strategy probability" << std::endl;
    std::cout << "# --pb ... balance exploration / exploitation" << std::endl;
    std::cout << "# -pc ... elitist parameter probability" << std::endl;
}

