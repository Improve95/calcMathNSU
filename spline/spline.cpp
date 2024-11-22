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

vector<vector<double>> findAbcdSplineRatio(vector<double> &cVector) {

}

vector<double> findCVector(double a, double b, double intervalNumber) {
    double h_i = (abs(a) + abs(b)) / intervalNumber;
    vector<double> points;
    for (int i = 0; i < intervalNumber + 1; i++) {
        points.push_back(a + h_i * i);
    }

    ModuleFunc moduleFunc;

    vector<vector<double>> acbRatio;

    acbRatio.push_back({0, 2 * h_i, h_i});
    for (int i = 1; i < intervalNumber - 2; i++) {
        acbRatio.push_back({h_i, 2 * h_i, h_i});
    }
    acbRatio.push_back({h_i, 2 * h_i, 0});

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
    for (auto c_i : findRootsByRunThroughMethod(acbRatio, fVector)) {
        cVector.push_back(c_i);
    }
    cVector.push_back(0);

    return cVector;
}

int main() {
    double a = -1;
    double b = 1;
    int intervalNumber = 4;

    vector<double> cVector = findCVector(a, b, intervalNumber);
    vector<vector<double>> abcdRatio = findAbcdSplineRatio(cVector);

    return 0;
}