#ifndef RUN_THROUGH_METHOD_H
#define RUN_THROUGH_METHOD_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

vector<double> findRootsByRunThroughMethod(vector<vector<double>> &abcRatio, vector<double> &d) {
    int matrixSize = abcRatio.size();

    vector<double> alphaVector(matrixSize, 0);
    vector<double> betaVector(matrixSize, 0);

    alphaVector[0] = abcRatio[0][2] / abcRatio[0][1];
    betaVector[0] = d[0] / abcRatio[0][1];

    for (int i = 1; i < matrixSize ; i++) {
        double a_i = abcRatio[i][0];
        double b_i = abcRatio[i][1];
        double c_i = abcRatio[i][2];

        double denominator = b_i + a_i * alphaVector[i - 1];

        alphaVector[i] = -c_i / denominator;
        betaVector[i] = (d[i] - a_i * betaVector[i - 1]) / denominator;
    }

    vector<double> roots(matrixSize, 0.0);
    roots[matrixSize - 1] = betaVector[matrixSize - 1];
    for (int i = matrixSize - 2; i >= 0; --i) {
        roots[i] = alphaVector[i] * roots[i + 1] + betaVector[i];
    }

    return roots;
}

#endif
