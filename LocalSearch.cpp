//
// Created by osmangokalp on 5/31/2020.
//

#include "LocalSearch.h"

void LocalSearch::oneExchange(Problem &problem, int l, bool firstImp, int *sol, double &scoreSol, int &numEval) const {
    int n = problem.getN();
    int t = problem.getT();

    int bestRow = -1, bestStartIndex = -1;
    double bestScore = scoreSol;

    for (int row = 0; row < t; ++row) {
        int temp = sol[row];

        for (int si = 0; si < n - l + 1; ++si) {
            sol[row] = si;
            ConsensusString cs = problem.calculateConsensusString(sol, t, l);
            numEval++;
            double score = cs.getSimilarity();

            if (score > bestScore) {
                bestScore = score;
                bestRow = row;
                bestStartIndex = si;

                if (firstImp) { //first imp.
                    scoreSol = bestScore;
                    return;
                }
            }
        }

        sol[row] = temp; //restore original value
    }

    if (bestScore > scoreSol) { //there is an improvement
        sol[bestRow] = bestStartIndex;
        scoreSol = bestScore;
    }

}
