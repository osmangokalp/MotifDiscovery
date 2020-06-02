//
// Created by osmangokalp on 5/31/2020.
//

#include "LocalSearch.h"

void LocalSearch::oneExchange(Problem &problem, int l, bool impType, int *S, int scoreS, int &numEval) {
    int n = problem.getN();
    int t = problem.getT();

    for (int row = 0; row < t; ++row) {
        for (int si = 0; si < n - l + 1; ++si) {
            if (S[row] != si) {
                int temp = S[row];
                S[row] = si;
                ConsensusString cs = problem.calculateConsensusString(S, t, l);
                double score = cs.getSimilarity();
                if (score > scoreS) {
                    best imp ? first imp?
                }
            }
        }
    }
}
