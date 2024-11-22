#include <iostream>
#include <vector>
#include "RunThroughMethod.h"

using namespace std;

class ModuleFunc {

public:
    double value(double x) {
        return abs(x);
    }
};

vector<vector<double>> findAbcdSplineRatio(vector<double> &cVector, double h_i,
                                           vector<double> &points, ModuleFunc moduleFunc) {

    int cVectorSize = cVector.size();

    vector<double> dVector;
    for (int i = 0; i < cVectorSize - 1; i++) {
        double d_i = (cVector[i + 1] - cVector[i]) / h_i;
        dVector.push_back(d_i);
    }

    vector<double> bVector;
    for (int i = 0; i < cVectorSize - 1; i++) {
        double f_value_cur = moduleFunc.value(points[i]);
        double f_value_next = moduleFunc.value(points[i + 1]);
        double b_i = (f_value_next - f_value_cur - pow(h_i, 2) * cVector[i] - pow(h_i, 3) * dVector[i]) / h_i;
        bVector.push_back(b_i);
    }

    vector<double> aVector;
    for (int i = 0; i < cVectorSize - 1; i++) {
        aVector.push_back( moduleFunc.value(points[i]));
    }

    vector<vector<double>> abcdRatioVector {
        aVector, bVector, cVector, dVector
    };
    return abcdRatioVector;
}

vector<double> findCVector(double intervalNumber, double h_i,
                           vector<double> &points, ModuleFunc &moduleFunc) {

    vector<vector<double>> acbRatio;
    acbRatio.push_back({0, 4 * h_i, h_i});
    for (int i = 1; i < intervalNumber - 2; i++) {
        acbRatio.push_back({h_i, 4 * h_i, h_i});
    }
    acbRatio.push_back({h_i, 4 * h_i, 0});

    vector<double> fVector;
    for (int i = 0; i < intervalNumber - 1; i++) {
        double f_value_i = moduleFunc.value(points[i]);
        double f_value_i1 = moduleFunc.value(points[i + 1]);
        double f_value_i2 = moduleFunc.value(points[i + 2]);

        double f_i = 6 * ((f_value_i2 - f_value_i1) / h_i - (f_value_i1 - f_value_i) / h_i);
        fVector.push_back(f_i);
    }

    vector<double> cVector;
    cVector.push_back(0);
    vector<double> roots = findRootsByRunThroughMethod(acbRatio, fVector);
    for (auto c_i : roots) {
        cVector.push_back(c_i);
    }
    cVector.push_back(0);

    return cVector;
}

int main() {
    double a = -1;
    double b = 1;
    int intervalNumber = 4;

    ModuleFunc moduleFunc;

    double h_i = (abs(a) + abs(b)) / intervalNumber;
    vector<double> points;
    for (int i = 0; i < intervalNumber + 1; i++) {
        points.push_back(a + h_i * i);
    }

    vector<double> cVector = findCVector(intervalNumber, h_i, points, moduleFunc);

    vector<vector<double>> abcdRatio = findAbcdSplineRatio(cVector, h_i, points, moduleFunc);

    return 0;
}