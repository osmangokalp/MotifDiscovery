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
    delete [] sequences;
}

Problem::Problem(const std::string &fileName) : fileName(fileName) {
    std::ifstream file("../TRANSFAC_Dataset/Real/" + fileName);

    std::string line;

    while (getline (file, line)) {
        // Output the text from the file
        std::cout << line << "\n";
    }
}
