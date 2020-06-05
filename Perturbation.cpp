//
// Created by osmangokalp on 4.06.2020.
//

#include <vector>
#include <random>
#include "Perturbation.h"

int *Perturbation::perturb(Problem &problem, int l, int *sol, int k, std::default_random_engine generator) const {
    int t = problem.getT();
    int n = problem.getN();
    int *solPerturbed = new int[t];

    for (int i = 0; i < t; ++i) {
        solPerturbed[i] = sol[i];
    }

    std::vector<int> v(t);
    for (int i = 0; i < v.size(); ++i) {
        v[i] = i;
    }

    for (int j = 0; j < k; ++j) {
        int randRowIndex = generator() % (t); //random row index

        int beforeStartIndex = solPerturbed[randRowIndex];
        int randStartIndex = beforeStartIndex;

        while (beforeStartIndex == randStartIndex) {
            randStartIndex = generator() % (n - l + 1);
        }

        solPerturbed[randRowIndex] = randStartIndex;

        v.erase(v.begin() + randRowIndex);
    }

    return solPerturbed;
}
