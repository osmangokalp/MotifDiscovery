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

double Problem::calculateSimilarity(int *positionVector, int l) const {
    double sim = -1;

    try {
        if (l < 0) {
            throw std::string("Motif length must be positive.");
        }

        double **profileMatrix = new double *[4]; //row order: A, T, G, C
        for (int k = 0; k < 4; ++k) {
            profileMatrix[k] = new double[l];
        }

        for (int i = 0; i < l; ++i) {
            int countA = 0;
            int countT = 0;
            int countG = 0;
            int countC = 0;

            int numOfSkippedSequences = 0;
            for (int j = 0; j < this->t; ++j) {
                int startIndex = positionVector[j];

                if (startIndex < 0) { //negative index means that the sequence will not be calculated
                    numOfSkippedSequences++;
                    continue;
                }

                if (startIndex + l > this->n) {
                    throw std::string("Too long motif. Start index of the motif must be <= n - l.");
                }

                char gene = sequences[j][startIndex + i];
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

            int numOfEvaluatedSequences = this->t - numOfSkippedSequences;
            profileMatrix[0][i] = (1.0 / numOfEvaluatedSequences) * countA;
            profileMatrix[1][i] = (1.0 / numOfEvaluatedSequences) * countT;
            profileMatrix[2][i] = (1.0 / numOfEvaluatedSequences) * countG;
            profileMatrix[3][i] = (1.0 / numOfEvaluatedSequences) * countC;
        }

        //calculate similarity
        double totalMax = 0.0;
        for (int i = 0; i < l; ++i) {
            double max = profileMatrix[0][i];
            if (profileMatrix[1][i] > max) {
                max = profileMatrix[1][i];
            }
            if (profileMatrix[2][i] > max) {
                max = profileMatrix[2][i];
            }
            if (profileMatrix[3][i] > max) {
                max = profileMatrix[3][i];
            }
            totalMax += max;
        }

        sim = totalMax / l;

        //free profile matrix
        for (int i = 0; i < 4; ++i) {
            delete[] profileMatrix[i];
        }
        delete[] profileMatrix;

        return sim;
    }
    catch (std::string msg) {
        std::cerr << msg << std::endl;
        std::exit(1);
    }
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

double **Problem::constructProfileMatrix(char **alignmentMatrix, int numRow, int l) {
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
