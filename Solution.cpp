//
// Created by osmangokalp on 5.06.2020.
//

#include <cstring>
#include <iostream>
#include "Solution.h"

Solution::Solution(int len) : len(len) {
    //std::cout << "NORMAL CONSTRUCTOR RUN" << std::endl;
    startIndices = new int[len];
    for (int i = 0; i < len; ++i) {
        startIndices[i] = -1; //assign default value
    }
    similarityScore = 0.0;
    consensusString = "";
}

Solution::~Solution() {
    //std::cout << "DESTRUCTOR RUN" << std::endl;
    delete[] startIndices;
}
