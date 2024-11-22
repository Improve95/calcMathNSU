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
        return ai + bi * hi + ci * pow(hi, 2) + di * pow(hi, 3);
    }

    double der1() {
        return bi + 2 * ci * hi + 3 * di * pow(hi, 2);
    }

    double der2() {
        return 2 * ci + 6 *  di * hi;
    }

    void setNextSplineRatio(double ai, double bi, double ci, double di) {
        this->ai = ai;
        this->bi = bi;
        this->ci = ci;
        this->di = di;
    }
};

double createSpline(Spline &spline, ModuleFunc &moduleFunc) {
    return 0;
}

#endif
