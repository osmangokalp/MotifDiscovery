//
// Created by osmangokalp on 5/31/2020.
//

#ifndef MOTIFDISCOVERY_LOCALSEARCH_H
#define MOTIFDISCOVERY_LOCALSEARCH_H


#include "Problem.h"

class LocalSearch {
public:
    void oneExchange(Problem &problem, int l, bool impType, int *sol, int scoreSol, int &numEval);
};


#endif //MOTIFDISCOVERY_LOCALSEARCH_H
