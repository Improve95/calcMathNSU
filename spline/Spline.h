#ifndef SPLINE_H
#define SPLINE_H

#include <math.h>
#include "ModuleFunc.h"

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

    void setNextSplineRatio(double ai, double bi, double ci, double di) {
        this->ai = ai;
        this->bi = bi;
        this->ci = ci;
        this->di = di;
    }

    void calcAndSetNextAi() {

    }
};

double createSpline(Spline &spline, ModuleFunc &moduleFunc) {
    return 0;
}

#endif
