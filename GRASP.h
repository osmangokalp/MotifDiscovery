//
// Created by osmangokalp on 5/18/2020.
//

#ifndef MOTIFDISCOVERY_GRASP_H
#define MOTIFDISCOVERY_GRASP_H


#include "Problem.h"

class GRASP {
public:
    int *GRASPMotifSearch(Problem &problem, int l, double alpha, double cadidateRatio, int SEED, int MAX_EVAL) const;
};


#endif //MOTIFDISCOVERY_GRASP_H
