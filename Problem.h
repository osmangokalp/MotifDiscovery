//
// Created by osmangokalp on 5/4/2020.
//

#ifndef MOTIFDISCOVERY_PROBLEM_H
#define MOTIFDISCOVERY_PROBLEM_H

#include <string>

class Problem {
public:
    Problem(const std::string &fileName);

    virtual ~Problem();

    const std::string &getFileName() const;

    int getN() const;

    int getL() const;

    std::string *getSequences() const;

private:
    std::string fileName;
    int N; //number of sequences
    int L; //sequence length
    std::string *sequences;
};


#endif //MOTIFDISCOVERY_PROBLEM_H
