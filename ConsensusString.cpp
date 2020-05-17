//
// Created by osmangokalp on 5/17/2020.
//

#include <iostream>
#include "ConsensusString.h"

double ConsensusString::getSimilarity() const {
    return similarity;
}

const std::string &ConsensusString::getSequence() const {
    return sequence;
}

ConsensusString::ConsensusString(const std::string &sequence, double similarity) : sequence(sequence),
                                                                                   similarity(similarity) {}


