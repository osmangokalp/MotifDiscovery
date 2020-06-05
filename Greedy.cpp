//
// Created by osmangokalp on 5/13/2020.
//

#include "Greedy.h"

/**
 * Implementation of the GRASPMotifSearch algorithm in book
 * "An introduction to bioinformatics algorithms", Jones N.C., Pevzner P.A., 2004, MIT Press.
 * @param problem
 * @param l the motif length (searching for l-mer)
 * @return bestMotifIndexArray found
 */
Solution Greedy::GreedyMotifSearch(Problem &problem, int l) const {
    int n = problem.getN();
    int t = problem.getT();

    Solution bestSolution(t);
    bestSolution.startIndices[0] = 0;
    bestSolution.startIndices[1] = 0;

    problem.evaluateSolution(bestSolution, 2, l);

    //create and init incumbent solution
    Solution solution(t);

    for (int s0 = 0; s0 < n - l + 1; ++s0) {
        for (int s1 = 0; s1 < n - l + 1; ++s1) {
            solution.startIndices[0] = s0;
            solution.startIndices[1] = s1;
            problem.evaluateSolution(solution, 2, l);
            if (solution.similarityScore > bestSolution.similarityScore) {
                bestSolution = solution; //deep copy
            }
        }
    }

    solution = bestSolution; //continue with the deep copy of the best solution so far

    for (int i = 2; i < t; ++i) {
        bestSolution.startIndices[i] = 0; //include index i into calculation (change default value -1 that means sequence i will not be used)
        problem.evaluateSolution(bestSolution, i + 1, l);
        for (int si = 0; si < n - l + 1; ++si) {
            solution.startIndices[i] = si;
            problem.evaluateSolution(solution, i + 1, l);
            if (solution.similarityScore > bestSolution.similarityScore) {
                bestSolution = solution;
            }
        }
        solution = bestSolution;
    }

    return bestSolution;
}
