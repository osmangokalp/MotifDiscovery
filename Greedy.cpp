//
// Created by osmangokalp on 5/13/2020.
//

#include "Greedy.h"

/**
 * Implementation of the GreedyMotifSearch algorithm in book
 * "An introduction to bioinformatics algorithms", Jones N.C., Pevzner P.A., 2004, MIT Press.
 * @param problem
 * @param bestMotifIndexArray to be found
 * @param l the motif length (searching for l-mer)
 */
void Greedy::GreedyMotifSearch(Problem *problem, int *bestMotifIndexArray, int l) const {
    int n = problem->getN();
    int t = problem->getT();

    //init best motif index array
    for (int i = 0; i < t; ++i) {
        if (i == 0 || i == 1) {
            bestMotifIndexArray[i] = 0;
        } else {
            bestMotifIndexArray[i] = -1;
        }

    }

    double scoreBestMotif = problem->calculateConsensusString(bestMotifIndexArray, 2, l).getSimilarity();

    //create and init temp motif array
    int *s = new int[t];
    for (int i = 0; i < t; ++i) {
        s[i] = -1;
    }

    for (int s0 = 0; s0 < n - l + 1; ++s0) {
        for (int s1 = 0; s1 < n - l + 1; ++s1) {
            s[0] = s0;
            s[1] = s1;
            double scoreS = problem->calculateConsensusString(s, 2, l).getSimilarity();
            if (scoreS > scoreBestMotif) {
                bestMotifIndexArray[0] = s0;
                bestMotifIndexArray[1] = s1;
                scoreBestMotif = scoreS;
            }
        }
    }

    s[0] = bestMotifIndexArray[0];
    s[1] = bestMotifIndexArray[1];

    for (int i = 2; i < t; ++i) {
        bestMotifIndexArray[i] = 0; //include index i into calculation (change default value -1 that means sequence i will not be used)
        scoreBestMotif = problem->calculateConsensusString(bestMotifIndexArray, i + 1, l).getSimilarity();
        for (int si = 0; si < n - l + 1; ++si) {
            s[i] = si;
            double scoreS = problem->calculateConsensusString(s, i + 1, l).getSimilarity();
            if (scoreS > scoreBestMotif) {
                bestMotifIndexArray[i] = si;
                scoreBestMotif = scoreS;
            }
        }
        s[i] = bestMotifIndexArray[i];
    }

    delete[] s;
}
