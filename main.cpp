#include <iostream>
#include <fstream>
#include <string>
#include "Problem.h"

using namespace std;

int main () {
    Problem *p = new Problem("hm03r.fasta");

    delete p;

    return 0;
}
