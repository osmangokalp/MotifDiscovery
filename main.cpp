#include <iostream>
#include <string>
#include "Problem.h"
#include "Greedy.h"
#include "GRASP.h"
#include "LocalSearch.h"
#include "Perturbation.h"

int main () {
    Problem p("hm03r.fasta");
    int l = 10;
    double alpha = 1.0;
    double candidateRatio = 0.2;
    int SEED = 101;
    std::default_random_engine generator(SEED);
    int MAX_EVAL = p.getN() * (p.getN() - 1)  * 0.5 + (p.getT() - 2) * p.getN();
    int *bestMotifIndexArray;

    GRASP grasp;
    bestMotifIndexArray = grasp.GRASPMotifSearch(p, l, alpha, candidateRatio, generator, MAX_EVAL);

    //Greedy greedy;
    //bestMotifIndexArray = greedy.GreedyMotifSearch(p, l);

    int numRow = p.getT();

    std::cout << "Best motif index array:";
    for (int i = 0; i < p.getT(); ++i) {
        std::cout << bestMotifIndexArray[i] << ", ";
    }

    char** am = p.constructAlignmentMatrix(bestMotifIndexArray, numRow, l);
    std::cout << std::endl << "Alignment matrix:" << std::endl;
    for (int i = 0; i < numRow; ++i) {
        for (int j = 0; j < l; ++j) {
            std::cout << am[i][j];
        }
        std::cout << std::endl;
    }

    double** pm = p.constructProfileMatrix(am, numRow, l);
    std::cout << std::endl << "Profile matrix:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < l; ++j) {
            std::cout << pm[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    ConsensusString cs = p.constructConsensusString(pm, l);
    std::cout << "Consensus string: " << cs.getSequence() << std::endl;
    std::cout << "Consensus similarity: " << cs.getSimilarity() << std::endl;

    //free
    for (int i = 0; i < numRow; ++i) {
        delete[] am[i];
    }
    delete[] am;

    for (int i = 0; i < 4; ++i) {
        delete[] pm[i];
    }
    delete[] pm;

    delete[] bestMotifIndexArray;

    return 0;
}
