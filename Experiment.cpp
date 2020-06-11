//
// Created by osmangokalp on 10.06.2020.
//

#include "Experiment.h"
#include "GRASP.h"
#include <fstream>
#include <iostream>

void Experiment::saveToAFile(std::string outputFileName, std::string line) const {
    std::ofstream outFile;
    outFile.open(experimentsFolder + std::string("/") + outputFileName, std::ios_base::app);
    if (outFile.fail()) {
        std::cerr << "unable to open file << outputFileName << for writing" << std::endl;
        exit(1);
    }
    outFile << line << std::endl;
    outFile.close();
}

Experiment::Experiment(const std::string &experimentsFolder) : experimentsFolder(experimentsFolder) {}

void Experiment::doGRASPExperiment(int numTry, int maxEval, int motifLength, std::string problemInstanceName) const {
    GRASP grasp;

    double alphaArr[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    double candidateRatioArr[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
    bool firstImpArr[] = {true, false};

    Problem problem(problemInstanceName);

    for (int i = 0; i < 2; ++i) {
        bool firstImp = firstImpArr[i];
        for (int j = 0; j < 11; ++j) {
            double alpha = alphaArr[j];
            for (int k = 0; k < 10; ++k) {
                double candidateRatio = candidateRatioArr[k];
                for (int l = 0; l < numTry; ++l) {
                    std::default_random_engine generator(100 + l);
                    Solution *solution = grasp.GRASPMotifSearch(problem, motifLength, alpha, candidateRatio, firstImp,
                                                                generator, maxEval);
                    std::string line = problemInstanceName + " " +
                                       std::to_string(l) + " " + std::to_string(firstImp) + " " +
                                       std::to_string(alpha) + " " +
                                       std::to_string(candidateRatio) + " " + std::to_string(maxEval) + " " +
                                       std::to_string(motifLength) + " " + solution->consensusString + " " +
                                       std::to_string(solution->similarityScore);
                    saveToAFile("allResults.txt", line);
                }
            }
        }
    }
}
