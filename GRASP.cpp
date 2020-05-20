//
// Created by osmangokalp on 5/18/2020.
//

#include "GRASP.h"
#include <random>
#include <iostream>
#include <vector>

int *
GRASP::GRASPMotifSearch(Problem *problem, int l, double alpha, double cadidateRatio, int SEED, int MAX_EVAL) const {
    int n = problem->getN();
    int t = problem->getT();
    int *bestMotifIndexArray = new int[t];
    double bestScore = 0.0;
    int numEval = 0;

    std::default_random_engine generator(SEED);

    int candidateCount = (n - l + 1) * cadidateRatio;
    int *CL = new int[candidateCount]; //candidate list
    int *RCL = new int[candidateCount]; //restricted candidate list (max size: candidate list)
    double *scores = new double[candidateCount];
    int *s = new int[t]; //temp motif index array

    int GRASPIter = 0;
    while (numEval < MAX_EVAL) {
        std::cout << std::endl << "GRASP iteration: " << GRASPIter++ << std::endl;

        int s0 = generator() % (n - l + 1); //random start index

        //init s
        for (int i = 0; i < t; ++i) {
            if (i == 0) {
                s[i] = s0;
            } else {
                s[i] = -1;
            }
        }

        for (int row = 1; row < t; ++row) {
            //construct candiate list CL
            std::vector<int> v(n - l + 1);
            for (int i = 0; i < v.size(); ++i) {
                v[i] = i;
            }

            for (int i = 0; i < candidateCount; ++i) {
                int selectedIndex = generator() % v.size();
                int candidate = v[selectedIndex];
                CL[i] = candidate;
                v.erase(v.begin() + selectedIndex);
            }

            double max = 0.0;
            double min = 1.0;
            for (int j = 0; j < candidateCount; ++j) {
                s[row] = CL[j];
                double score = problem->calculateConsensusString(s, row + 1, l).getSimilarity();

                numEval++;

                scores[j] = score;
                if (score > max) {
                    max = score;
                }

                if (score < min) {
                    min = score;
                }
            }

            //construct RCL
            int RCLSize = 0;
            for (int k = 0; k < candidateCount; ++k) {
                if (scores[k] >= min + alpha * (max - min)) {
                    RCL[RCLSize++] = CL[k];
                }
            }

            //select random from RCL
            int selectedIndex = generator() % RCLSize;
            int selected = RCL[selectedIndex];
            s[row] = selected;
        }

        //calculate
        double scoreS = problem->calculateConsensusString(s, t, l).getSimilarity();

        numEval++;

        if (scoreS > bestScore) {
            bestScore = scoreS;
            std::cout << "New best: " << bestScore << std::endl;
            for (int i = 0; i < t; ++i) {
                bestMotifIndexArray[i] = s[i];
            }
        }
    }

    delete[] CL;
    delete[] RCL;
    delete[] s;
    delete[] scores;

    return bestMotifIndexArray;
}
