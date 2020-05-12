#include <iostream>
#include <fstream>
#include <string>
#include "Problem.h"

using namespace std;

int main () {
    Problem *p = new Problem("hm03r.fasta");
    int positionVector[] = {1243, 1166, 371, 184, 462, 732,  234, 1149, -1, -1};
    for (int i = 0; i < 8; ++i) {
        positionVector[i] = 1500 - positionVector[i] + 1;
    }

    std::cout << p->calculateSimilarity(positionVector, 20);

    delete p;


    return 0;
}
