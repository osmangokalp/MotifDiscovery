//
// Created by osmangokalp on 5.06.2020.
//

#ifndef MOTIFDISCOVERY_SOLUTION_H
#define MOTIFDISCOVERY_SOLUTION_H


#include <string>

class Solution {
public:
    int * startIndices;
    double similarityScore;
    int len;
    std::string consensusString;

    Solution(int len);

    virtual ~Solution();
};


#endif //MOTIFDISCOVERY_SOLUTION_H
