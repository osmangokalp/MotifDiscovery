//
// Created by osmangokalp on 5/18/2020.
//

#include "GRASP.h"
#include "LocalSearch.h"
#include <iostream>
#include <vector>

Solution *
GRASP::GRASPMotifSearch(Problem &problem, int l, double alpha, double candidateRatio, bool firstImp,
                        std::default_random_engine generator, int MAX_EVAL) const {
    int n = problem.getN();
    int t = problem.getT();
    Solution *bestSolution = nullptr; //best solution

    int numEval = 0;

    int candidateCount = (n - l + 1) * candidateRatio;
    int *CL = new int[candidateCount]; //candidate list
    int *RCL = new int[candidateCount]; //restricted candidate list (max size: candidate list)
    double *scores = new double[candidateCount];

    LocalSearch ls;

    int GRASPIter = -1;
    while (numEval < MAX_EVAL) {
        GRASPIter++;

        //init solution
        int s0 = generator() % (n - l + 1); //random start index
        Solution *solution = new Solution(t); //incumbent solution
        solution->startIndices[0] = s0;

        for (int rowIndex = 1; rowIndex < t; ++rowIndex) {
            //construct candidate list CL
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
                solution->startIndices[rowIndex] = CL[j];

                problem.evaluateSolution(solution, rowIndex + 1, l);
                numEval++;

                scores[j] = solution->similarityScore;
                if (scores[j] > max) {
                    max = scores[j];
                }

                if (scores[j] < min) {
                    min = scores[j];
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
            solution->startIndices[rowIndex] = selected;
        }

        //final evaluation of the produced solution before local search
        problem.evaluateSolution(solution, t, l);
        numEval++;

        bool imp;
        do {
            imp = false;
            double before = solution->similarityScore;
            ls.oneExchange(problem, l, firstImp, solution, numEval);
            double after = solution->similarityScore;
            if (after - before > 0) {
                imp = true;
            }
        } while (imp);

        //std::cout << "GRASP iteration " << GRASPIter << ", Sol: " << solution->similarityScore << std::endl;

        if (bestSolution == nullptr) {
            bestSolution = solution;
        } else {
            if (solution->similarityScore > bestSolution->similarityScore) {
                delete bestSolution;
                bestSolution = solution;
                //std::cout << "\tNEW BEST" << std::endl;
            } else {
                delete solution;
            }
        }
    }

    delete[] CL;
    delete[] RCL;
    delete[] scores;

    return bestSolution;
}
