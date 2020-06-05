//
// Created by osmangokalp on 5.06.2020.
//

#include <cstring>
#include <iostream>
#include "Solution.h"

Solution::Solution(int len) : len(len) {
    startIndices = new int[len];
    for (int i = 0; i < len; ++i) {
        startIndices[i] = -1; //assign default value
    }
}

Solution::~Solution() {
    delete[] startIndices;
}

Solution::Solution(const Solution &obj) {
    std::cout << "COPY CONSTRUCTOR RAN";
    len = obj.len;
    similarityScore = obj.similarityScore;
    consensusString = obj.consensusString;

    startIndices = new int[len];
    for (int i = 0; i < len; ++i) {
        startIndices[i] = obj.startIndices[i];
    }
}
