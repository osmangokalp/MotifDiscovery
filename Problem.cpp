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

    //find N
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

    this->L = sequences[0].size();

    for (int i = 0; i < N; i++) {
        std::cout << sequences[i] + "\n";
    }

}
