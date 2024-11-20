#include <iostream>
#include <math.h>

using namespace std;

class Spline {

private:
    double ai = 0;
    double bi = 0;
    double ci = 0;
    double di = 0;

    double xi = 0;
    double xi1 = 0;

public:
    double spline() {
        return ai + bi * hi() + ci / 2.0 * pow(hi(), 2) + di / 6.0 * pow(hi(), 3);
    }

    double der1() {
        return bi + ci * hi() + di / 2.0 * pow(hi(), 2);
    }

    double der2() {
        return ci + di * hi();
    }

    double setNextSplineRatio(double ai, double bi, double ci, double di) {
        this->ai = ai;
        this->bi = bi;
        this->ci = ci;
        this->di = di;
    }

    double setNextXi(double xi1) {
        this->xi = this->xi1;
        this->xi1 = xi1;
    }

private:
    double hi() {
        return xi1 - xi;
    }
};

int main() {
    cout << "hello world" << endl;

    return 0;
}