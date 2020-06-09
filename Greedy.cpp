//
// Created by osmangokalp on 5/13/2020.
//

#include <iostream>
#include "Greedy.h"

/**
 * Implementation of the GRASPMotifSearch algorithm in book
 * "An introduction to bioinformatics algorithms", Jones N.C., Pevzner P.A., 2004, MIT Press.
 * @param problem
 * @param l the motif length (searching for l-mer)
 * @return bestMotifIndexArray found
 */
Solution *Greedy::GreedyMotifSearch(Problem &problem, int l) const {
    int n = problem.getN();
    int t = problem.getT();

    Solution *bestSolution = new Solution(t);
    bestSolution->startIndices[0] = 0;
    bestSolution->startIndices[1] = 0;

    problem.evaluateSolution(bestSolution, 2, l);

    //create and init incumbent solution
    Solution *solution = new Solution(t);

    for (int s0 = 0; s0 < n - l + 1; ++s0) {
        for (int s1 = 0; s1 < n - l + 1; ++s1) {
            solution->startIndices[0] = s0;
            solution->startIndices[1] = s1;
            problem.evaluateSolution(solution, 2, l);
            if (solution->similarityScore > bestSolution->similarityScore) {
                delete bestSolution;
                bestSolution = solution;
                solution = new Solution(t);
            }
        }
    }

    solution->startIndices[0] = bestSolution->startIndices[0];
    solution->startIndices[1] = bestSolution->startIndices[1];

    for (int i = 2; i < t; ++i) {
        bestSolution->startIndices[i] = 0; //include index i into calculation (default value -1 that means sequence i will not be used)
        problem.evaluateSolution(bestSolution, i + 1, l);

        for (int j = 0; j < i + 1; ++j) { //copy first parts from the best solution
            solution->startIndices[j] = bestSolution->startIndices[j];
        }

        for (int si = 0; si < n - l + 1; ++si) {
            solution->startIndices[i] = si;
            problem.evaluateSolution(solution, i + 1, l);

            std::cout << std::endl << "sol:" << std::endl;
            std::cout << "Sim: " << solution->similarityScore << std::endl;
            for (int m = 0; m < i + 1; ++m) {
                std::cout << solution->startIndices[m] << std::endl ;
            }

            if (solution->similarityScore > bestSolution->similarityScore) {
                delete bestSolution;
                bestSolution = solution;
                solution = new Solution(t);
                for (int j = 0; j < i; ++j) {
                    solution->startIndices[j] = bestSolution->startIndices[j];
                }
            }
        }
    }

    return bestSolution;
}
