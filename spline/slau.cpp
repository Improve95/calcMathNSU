#include <iostream>
#include <vector>
#include "Spline.h"
#include "ModuleFunc.h"
#include "RunThroughMethod.h"

using namespace std;

vector<vector<double>> matrixInitialize(int intervalNumber) {
    vector<vector<double>> matrix(intervalNumber, vector<double>(3, 0));
    return matrix;
}

void fillMatrixAndEquation(vector<vector<double>> &matrix, vector<double> &equation) {
    matrix[0] = {0, 2, 1};
    matrix[1] = {1, 3, 2};
    matrix[2] = {1, 4, 0};

    equation = {5, 10, 11};

//    matrix[0] = {0, 4, 3};
//    matrix[1] = {2, 5, 2};
//    matrix[2] = {1, 7, 8};
//    matrix[3] = {3, 5, 0};
//
//    equation = {5, 6, 7, 9};
}

int main() {
    Spline spline;
    ModuleFunc moduleFunc;
    int intervalNumber = 4 - 1;

    /*
    double a = -1;
    double b = 1;

    double hi = (abs(a) + abs(b)) / abs(pointsNumber - 1);*/

    vector<vector<double>> matrix = matrixInitialize(intervalNumber);
    vector<double> equations(intervalNumber);

    fillMatrixAndEquation(matrix, equations);

    vector<double> roots = findRootsByRunThroughMethod(matrix, equations);

    for (double root : roots) {
        cout << root << " ";
    }

    return 0;
}