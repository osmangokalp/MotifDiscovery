//
// Created by osmangokalp on 5/17/2020.
//

#ifndef MOTIFDISCOVERY_CONSENSUSSTRING_H
#define MOTIFDISCOVERY_CONSENSUSSTRING_H


class ConsensusString {
public:
    ConsensusString(const std::string &sequence, double similarity);

    const std::string &getSequence() const;

    double getSimilarity() const;

private:
    std::string sequence;
    double similarity;
};


#endif //MOTIFDISCOVERY_CONSENSUSSTRING_H
