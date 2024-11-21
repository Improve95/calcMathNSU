#ifndef RUN_THROUGH_METHOD_H
#define RUN_THROUGH_METHOD_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

double calculateNextCi() {
    return 0;
}

double calculateNextBi() {
    return 0;
}

double calculateNextAi() {
    return 0;
}

vector<double> findRootsByRunThroughMethod(vector<vector<double>> &matrix, vector<double> &equation) {
    int matrixSize = matrix.size();

    vector<double> alphaVector(matrixSize, 0);
    vector<double> betaVector(matrixSize, 0);

    vector<double> rowi = matrix[0];
    vector<double> prevRowi;
    betaVector[0] = equation[0] / rowi[1];

    for (int i = 1; i < matrixSize; i++) {
        prevRowi = rowi;
        rowi = matrix[i];
        alphaVector[i] = rowi[2] / (rowi[1] + rowi[0] * alphaVector[i - 1]);
        betaVector[i] = (equation[i] - alphaVector[i] * betaVector[i - 1]) / (rowi[1] + rowi[0] * alphaVector[i - 1]);
    }

    vector<double> roots(matrixSize);
    roots[matrixSize - 1] = betaVector[matrixSize - 1];
    for (int i = matrixSize - 2; i >= 0; i--) {
        roots[i] = alphaVector[i] * roots[i + 1] + betaVector[i];
    }

    return roots;
}

#endif
