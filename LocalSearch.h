//
// Created by osmangokalp on 5/31/2020.
//

#ifndef MOTIFDISCOVERY_LOCALSEARCH_H
#define MOTIFDISCOVERY_LOCALSEARCH_H


#include "Problem.h"

class LocalSearch {
public:
    void oneExchange(Problem &problem, int l, bool firstImp, int *sol, double &scoreSol, int &numEval) const;
};


#endif //MOTIFDISCOVERY_LOCALSEARCH_H
