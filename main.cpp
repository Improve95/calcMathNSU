#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class Function {

public:
    virtual double value(double x);
};

class QuadFunction : Function {

private:
    double a;
    double b;
    double c;

public:
    QuadFunction(double a, double b, double c, double d) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    double getA() const {
        return a;
    }

    double getB() const {
        return b;
    }

    double getC() const {
        return c;
    }

    virtual double value(double x) {
        return a * pow(x, 2) + b * x + c;
    }
};


class CubFunction : Function {

private:
    double a;
    double b;
    double c;
    double d;

public:
    CubFunction(double a, double b, double c, double d) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

    double getA() const {
        return a;
    }

    double getB() const {
        return b;
    }

    double getC() const {
        return c;
    }

    double getD() const {
        return d;
    }

    virtual double value(double x) {
        return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
    }
};

double findDiscriminant(QuadFunction quadFunction) {
    return quadFunction.getB() * quadFunction.getB() - 4 * quadFunction.getA() * quadFunction.getC();
}

bool isInInterval(double value, double equal, double epsilon) {
    return (value + epsilon >= equal && value <= equal) ||
           (value - epsilon <= equal && value >= equal);
}

double doDichotomy(Function function, double leftBorder, double rightBorder,
                          double epsilon, double equalNumber, bool functionIsIncrease) {

    double reverseFuncValue = 1;
    if (!functionIsIncrease) {
        reverseFuncValue = -1;
    }

    double currentX = (rightBorder + leftBorder) / 2;

    while (true) {
        double funcValue = function.value(currentX) * reverseFuncValue;
        if (isInInterval(funcValue, equalNumber, epsilon)) {
            return currentX;
        } else if (funcValue > equalNumber) {
            currentX = (leftBorder + currentX) / 2;
        } else {
            currentX = (rightBorder + currentX) / 2;
        }
    }
}

vector<double> solveQuadEquation(double a, double b, double c) {

}

vector<double> solveCubEquation(double a, double b, double c, double d) {

}



int main() {

    return 0;
}
