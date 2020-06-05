//
// Created by osmangokalp on 5/4/2020.
//

#include "Problem.h"
#include <string>
#include <iostream>
#include <fstream>

int Problem::getT() const {
    return t;
}

int Problem::getN() const {
    return n;
}

std::string *Problem::getSequences() const {
    return sequences;
}

const std::string &Problem::getFileName() const {
    return fileName;
}

Problem::~Problem() {
    delete[] sequences;
}

Problem::Problem(const std::string &fileName) : fileName(fileName) {
    std::ifstream file("../TRANSFAC_Dataset/Real/" + fileName);

    std::string line;

    //find t, the number of sequences
    int counter = 0;
    while (getline(file, line)) {
        if (line[0] == '>') { // >seq_x line
            counter++;
        }
    }

    this->t = counter;
    this->sequences = new std::string[t];

    file.clear();
    file.seekg(0, std::ios::beg);

    counter = 0;
    while (getline(file, line)) {
        if (line[0] == '>') { //sequence label line
            getline(file, line); //read real sequence
            sequences[counter++] = line;
        }
    }

    file.close();

    //find n, the sequence length
    this->n = sequences[0].size();
}

void Problem::evaluateSolution(Solution &sol, int numRow, int l) const {
    double sim = -1;

    char **alignmentMatrix = constructAlignmentMatrix(sol.startIndices, numRow, l);
    double **profileMatrix = constructProfileMatrix(alignmentMatrix, numRow, l);
    ConsensusString consensusString = constructConsensusString(profileMatrix, l);

    //free memory
    for (int i = 0; i < numRow; ++i) {
        delete[] alignmentMatrix[i];
    }
    delete[] alignmentMatrix;

    for (int i = 0; i < 4; ++i) {
        delete[] profileMatrix[i];
    }
    delete[] profileMatrix;

    sol.consensusString = consensusString.getSequence();
    sol.similarityScore = consensusString.getSimilarity();
}

char **Problem::constructAlignmentMatrix(int *positionVector, int numRow, int l) const {

    try {
        if (l <= 0) {
            throw std::string("Motif length must be positive.");
        }

        char **alignmentMatrix = new char *[numRow];
        for (int i = 0; i < numRow; ++i) {
            alignmentMatrix[i] = new char[l];
        }

        for (int i = 0; i < l; ++i) {
            int rowIndex = 0;
            for (int j = 0; j < this->t; ++j) {
                int startIndex = positionVector[j];

                if (startIndex < 0) { //negative index means that the sequence will not be used
                    continue;
                }

                if (startIndex + l > this->n) {
                    throw std::string("Too long motif. Start index of the motif must be <= n - l.");
                }

                char gene = sequences[j][startIndex + i];
                alignmentMatrix[rowIndex++][i] = gene;
            }
        }

        return alignmentMatrix;
    }
    catch (std::string msg) {
        std::cerr << msg << std::endl;
        std::exit(1);
    }
}

ConsensusString Problem::constructConsensusString(double **profileMatrix, int l) const {
    std::string conSeq(l, '-');

    double maxTotal = 0;
    for (int i = 0; i < l; ++i) {
        int maxIndex = 0;
        double maxVal = profileMatrix[0][i];

        for (int j = 1; j < 4; ++j) {
            if (profileMatrix[j][i] > maxVal) {
                maxVal = profileMatrix[j][i];
                maxIndex = j;
            }
        }

        switch (maxIndex) {
            case 0:
                conSeq[i] = 'A';
                break;
            case 1:
                conSeq[i] = 'T';
                break;
            case 2:
                conSeq[i] = 'G';
                break;
            case 3:
                conSeq[i] = 'C';
                break;
        }

        maxTotal += maxVal;
    }

    double sim = maxTotal / l;

    return ConsensusString(conSeq, sim);
}

double **Problem::constructProfileMatrix(char **alignmentMatrix, int numRow, int l) const {
    double **profileMatrix = new double *[4]; //row order: A, T, G, C
    for (int k = 0; k < 4; ++k) {
        profileMatrix[k] = new double[l];
    }

    for (int i = 0; i < l; ++i) {
        int countA = 0;
        int countT = 0;
        int countG = 0;
        int countC = 0;

        for (int j = 0; j < numRow; ++j) {

            char gene = alignmentMatrix[j][i];
            switch (gene) {
                case 'A':
                    countA++;
                    break;
                case 'T':
                    countT++;
                    break;
                case 'G':
                    countG++;
                    break;
                case 'C':
                    countC++;
                    break;
                default:
                    throw std::string("Unexpected gene label: ") + gene + ". It should be A, C, G or T.";
            }
        }

        profileMatrix[0][i] = (1.0 / numRow) * countA;
        profileMatrix[1][i] = (1.0 / numRow) * countT;
        profileMatrix[2][i] = (1.0 / numRow) * countG;
        profileMatrix[3][i] = (1.0 / numRow) * countC;
    }

    return profileMatrix;
}
