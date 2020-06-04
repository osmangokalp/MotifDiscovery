//
// Created by osmangokalp on 4.06.2020.
//

#ifndef MOTIFDISCOVERY_PERTURBATION_H
#define MOTIFDISCOVERY_PERTURBATION_H


#include "Problem.h"

class Perturbation {
public:
    int *perturb(Problem &problem, int l, int *sol, int k, int SEED) const;
};


#endif //MOTIFDISCOVERY_PERTURBATION_H
