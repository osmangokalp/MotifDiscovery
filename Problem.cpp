//
// Created by osmangokalp on 5/4/2020.
//

#include "Problem.h"
#include <string>
#include <iostream>
#include <fstream>

int Problem::getN() const {
    return N;
}

int Problem::getL() const {
    return L;
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

    //find N, the number of sequences
    int counter = 0;
    while (getline(file, line)) {
        if (line[0] == '>') { // >seq_x line
            counter++;
        }
    }

    this->N = counter;
    this->sequences = new std::string[N];

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

    //find L, the sequence length
    this->L = sequences[0].size();
}

double Problem::calculateSimilarity(int *positionVector, int motifLength) const {
    double sim = -1;

    try {
        if (motifLength < 0) {
            throw std::string("Motif length must be positive.");
        }

        double **profileMatrix = new double*[4]; //row order: A, T, G, C
        for (int k = 0; k < 4; ++k) {
            profileMatrix[k] = new double [motifLength];
        }

        for (int i = 0; i < motifLength; ++i) {
            int countA = 0;
            int countT = 0;
            int countG = 0;
            int countC = 0;

            int numOfSkippedSequences = 0;
            for (int j = 0; j < this->N; ++j) {
                int startIndex = positionVector[j];

                if (startIndex < 0) { //negative index means that the sequence will not be calculated
                    numOfSkippedSequences++;
                    continue;
                }

                if (startIndex + motifLength > this->L) {
                    throw std::string("Too long motif. Start index of the motif must be <= L - motifLength.");
                }

                char gene = sequences[j][startIndex + i];
                switch (gene){
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

            int numOfEvaluatedSequences = this->N - numOfSkippedSequences;
            profileMatrix[0][i] = (1.0 / numOfEvaluatedSequences) * countA;
            profileMatrix[1][i] = (1.0 / numOfEvaluatedSequences) * countT;
            profileMatrix[2][i] = (1.0 / numOfEvaluatedSequences) * countG;
            profileMatrix[3][i] = (1.0 / numOfEvaluatedSequences) * countC;
        }

        //calculate similarity
        double totalMax = 0.0;
        for (int i = 0; i < motifLength; ++i) {
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

        sim = totalMax / motifLength;

        //free profile matrix
        for (int i = 0; i < 4; ++i) {
            delete [] profileMatrix[i];
        }
        delete [] profileMatrix;

        return sim;
    }
    catch (std::string msg) {
        std::cerr << msg << std::endl;
        std::exit(1);
    }
}
