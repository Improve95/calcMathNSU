#include <iostream>
#include <vector>
#include <fstream>
#include "RunThroughMethod.h"

using namespace std;

class ModuleFunc {

public:
    double value(double x) {
        return abs(x);
    }
};

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
        double b_i = (f_value_next - f_value_cur - pow(h_i, 2) * cVector[i] / 2 - pow(h_i, 3) * dVector[i] / 6) / h_i;
        bVector.push_back(b_i);
    }

    vector<double> aVector;
    for (int i = 0; i < cVectorSize - 1; i++) {
        aVector.push_back( moduleFunc.value(points[i]));
    }

    vector<vector<double>> abcdRatioVector;
    int ratioSize = aVector.size();
    for (int i = 0; i < ratioSize; i++) {
        abcdRatioVector.push_back({ aVector[i], bVector[i], cVector[i], dVector[i] });
    }

    return abcdRatioVector;
}

vector<vector<double>> createSplines(double a, double b, int intervalNumber, ModuleFunc moduleFunc) {
    double h_i = (abs(a) + abs(b)) / intervalNumber;
    vector<double> points;
    for (int i = 0; i < intervalNumber + 1; i++) {
        points.push_back(a + h_i * i);
    }

    vector<double> cVector = findCVector(intervalNumber, h_i, points, moduleFunc);

    return findAbcdSplineRatio(cVector, h_i, points, moduleFunc);
}

int main() {
    FILE *fileOut = fopen("spline.txt", "w");

    if (fileOut == NULL) {
        cerr <<  "file cannot open" << endl;
        throw exception();
    }

    double a = -1;
    double b = 1;
    vector<double> pointsNumberVector{ 5, 7, 11 };

    ModuleFunc moduleFunc;


    for (int i = 0; i < 3; i++) {
        int intervalNumber = pointsNumberVector[i] - 1;

        double h_i = (abs(a) + abs(b)) / intervalNumber;
        vector<double> points;
        for (int i = 0; i < intervalNumber + 1; i++) {
            points.push_back(a + h_i * i);
        }

        vector<vector<double>> splines = createSplines(a, b, intervalNumber, moduleFunc);

        for (auto splineRatio : splines) {
            double point = points[i];
            fprintf(fileOut, "(%f) + (%f*(x - (%f))) + (%f*(x - (%f))^2 / 2) + (%f*(x - (%f))^3 / 6)\n",
                    splineRatio[0], splineRatio[1], point, splineRatio[2], point, splineRatio[3], point);
        }
        fprintf(fileOut, "\n");
    }


    return 0;
}