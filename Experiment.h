//
// Created by osmangokalp on 10.06.2020.
//

#ifndef MOTIFDISCOVERY_EXPERIMENT_H
#define MOTIFDISCOVERY_EXPERIMENT_H


#include <string>

class Experiment {
public:
    std::string experimentsFolder;

    Experiment(const std::string &experimentsFolder);

    void saveToAFile(std::string outputFileName, std::string line) const;

    void doGRASPExperiment(int numTry, int maxEval, int motifLength, std::string problemInstanceName) const;
};


#endif //MOTIFDISCOVERY_EXPERIMENT_H
