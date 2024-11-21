#include <iostream>
#include <vector>
#include "Spline.h"
#include "ModuleFunc.h"
#include "RunThroughMethod.h"

using namespace std;

int main() {
    Spline spline;
    ModuleFunc moduleFunc;
    int intervalNumber = 4 - 1;

    /*
    double a = -1;
    double b = 1;

    double hi = (abs(a) + abs(b)) / abs(pointsNumber - 1);*/

    vector<vector<double>> abcRatio = {
            {0.0, 2.0, 1.0},
            {1.0, 3.0, 2.0},
            {1.0, 4.0, 0.0}
    };
    vector<double> equations = { 5.0, 1.0, 11.0 };

    vector<double> roots = findRootsByRunThroughMethod(abcRatio, equations);

    for (double root : roots) {
        cout << "x = " << root << endl;
    }

    return 0;
}