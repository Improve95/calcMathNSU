#include <iostream>
#include <math.h>

using namespace std;

class ModuleFunc {

public:
    double value(double x) {
        return abs(x);
    }
};

class Spline {

private:
    double ai;
    double bi;
    double ci;
    double di;

    double hi;
public:

    void setHi(double hi) {
        this->hi = hi;
    }

    double spline() {
        return ai + bi * hi + ci / 2.0 * pow(hi, 2) + di / 6.0 * pow(hi, 3);
    }

    double der1() {
        return bi + ci * hi + di / 2.0 * pow(hi, 2);
    }

    double der2() {
        return ci + di * hi;
    }

    double setNextSplineRatio(double ai, double bi, double ci, double di) {
        this->ai = ai;
        this->bi = bi;
        this->ci = ci;
        this->di = di;
    }

    void calcAndSetNextAi() {

    }
};

double createSpline(Spline &spline, ModuleFunc &moduleFunc) {

}

int main() {
    Spline spline;
    ModuleFunc moduleFunc;

    double a = -1;
    double b = 1;
    int pointsNumber = 5;

    double hi = (abs(a) + abs(b)) / abs(pointsNumber);
    return 0;
}