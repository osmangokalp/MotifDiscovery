//
// Created by osmangokalp on 5/4/2020.
//

#ifndef MOTIFDISCOVERY_PROBLEM_H
#define MOTIFDISCOVERY_PROBLEM_H

#include <string>
#include "ConsensusString.h"
#include "Solution.h"

class Problem {
public:
    Problem(const std::string &fileName);

    virtual ~Problem();

    const std::string &getFileName() const;

    /**
     *
     * @return the number of sequences
     */
    int getT() const;

    /**
     *
     * @return the sequence length
     */
    int getN() const;

    std::string *getSequences() const;

    void evaluateSolution(Solution *sol, int numRow, int l) const;

    char **constructAlignmentMatrix(int *positionVector, int numRow, int l) const;

    double **constructProfileMatrix(char **alignmentMatrix, int numRow, int l) const;

    ConsensusString constructConsensusString(double **profileMatrix, int l) const;

private:
    std::string fileName;
    int t; //number of sequences
    int n; //sequence length
    std::string *sequences;
};


#endif //MOTIFDISCOVERY_PROBLEM_H
