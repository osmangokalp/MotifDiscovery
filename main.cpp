#include <iostream>
#include <fstream>
#include <string>
#include "Problem.h"

using namespace std;

int main () {
    Problem *p = new Problem("hm03r.fasta");
    int positionVector[] = {4, 3, 0, 6, 9, 3, 0, 0, 2, 0};

    std::cout << p->calculateSimilarity(positionVector, 16);

    delete p;


    return 0;
}
