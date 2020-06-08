//
// Created by osmangokalp on 5/31/2020.
//

#include "LocalSearch.h"

void LocalSearch::oneExchange(Problem &problem, int l, bool firstImp, Solution *sol, int &numEval) const {
    int n = problem.getN();
    int t = problem.getT();

    int bestRow = -1, bestStartIndex = -1;
    double startScore = sol->similarityScore;
    double bestScore = startScore;

    for (int row = 0; row < t; ++row) {
        int temp = sol->startIndices[row];

        for (int si = 0; si < n - l + 1; ++si) {
            sol->startIndices[row] = si;
            problem.evaluateSolution(sol, t, l);
            numEval++;

            if (sol->similarityScore > bestScore) {

                if (firstImp) { //first imp.
                    return;
                }

                bestScore = sol->similarityScore;
                bestRow = row;
                bestStartIndex = si;
            }
        }

        sol->startIndices[row] = temp; //restore original value
    }

    if (bestScore > startScore) { //there is an improvement
        sol->startIndices[bestRow] = bestStartIndex;
    }

    problem.evaluateSolution(sol, t, l); //final evaluation
    numEval++;

}
