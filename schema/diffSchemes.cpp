#include <iostream>
#include <math.h>

using namespace std;

class Function {
  virtual double value(double x) = 0;
};

class sinus : public Function {

public:
    virtual double value(double x) {
        return sin(x);
    }
};

class Uj1 : public Function {

public:
    virtual double value(double x) {
        return 0;
    }
};

class Uj2 : public Function {

public:
    virtual double value(double x) {
        return 0;
    }
};

double calcNextFj() {

}

double calcNextUj() {

}

int main() {
    double a = 0, b = 10;
    int n1 = 100, n2 = 1000;
    double h1 = (b - a) / n1, h2 = (b - a) / n2;

    double t11 = 0.25 * h1, t12 = 0.5 * h1, t13 = 1 * h1, t14 = 1.25 * h1;
    double t21 = 0.25 * h2, t22 = 0.5 * h2, t23 = 1 * h2, t24 = 1.25 * h2;

    int T1 = 1, T2 = 2;

    

    return 0;
}