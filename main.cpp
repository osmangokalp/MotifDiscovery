#include <iostream>
#include <fstream>
#include <string>
#include "Problem.h"
#include "Greedy.h"

int main () {
    Problem *p = new Problem("hm03r.fasta");
    int positionVector[] = {1243, 1166, 371, 184, 462, 732,  234, 1149, -1, -1};
    for (int i = 0; i < 8; ++i) {
        positionVector[i] = 1500 - positionVector[i] + 1;
    }

    std::cout << p->calculateSimilarity(positionVector, 20) << std::endl;

    Greedy greedy;
    int l = 10;
    int *bestMotifIndexArray = new int[p->getT()];
    greedy.GreedyMotifSearch(p, bestMotifIndexArray, l);

    //bestMotifIndexArray[2] = -1;
    int numRow = 10;

    std::cout << "\nBest score: " << p->calculateSimilarity(bestMotifIndexArray, l) << std::endl;
    std::cout << "Best motif index array:";
    for (int i = 0; i < p->getT(); ++i) {
        std::cout << bestMotifIndexArray[i] << ", ";
    }

    std::cout << std::endl << "Alignment matrix:" << std::endl;
    for (int i = 0; i < p->getT(); ++i) {
        if (bestMotifIndexArray[i] == -1) {
            continue;
        }
        for (int j = bestMotifIndexArray[i]; j < bestMotifIndexArray[i] + l; ++j) {
            std::cout << p->getSequences()[i][j];
        }
        std::cout << std::endl;
    }

    char** am = p->constructAlignmentMatrix(bestMotifIndexArray, numRow, l);
    std::cout << std::endl << "Alignment matrix by method:" << std::endl;
    for (int i = 0; i < numRow; ++i) {
        for (int j = 0; j < l; ++j) {
            std::cout << am[i][j];
        }
        std::cout << std::endl;
    }

    double** pm = p->constructProfileMatrix(am, numRow, l);
    std::cout << std::endl << "Profile matrix:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < l; ++j) {
            std::cout << pm[i][j] << "\t";
        }
        std::cout << std::endl;
    }

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
    delete p;


    return 0;
}
