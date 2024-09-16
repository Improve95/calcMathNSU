#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

class Function {

public:
    virtual double value(double x) = 0;
};

class QuadFunction : public Function {

private:
    double a;
    double b;
    double c;

public:
    QuadFunction(double a, double b, double c) {
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

class CubFunction : public Function {

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
    return (value >= equal && value <= equal + epsilon) ||
            (value <= equal && value >= equal - epsilon);
}

double doDichotomy(Function &function, double leftBorder, double rightBorder,
                          double epsilon, double equalNumber, double reverseFuncValue) {

    double currentX = (rightBorder + leftBorder) / 2;

    while (true) {
        double funcValue = function.value(currentX) * reverseFuncValue;
         if (isInInterval(funcValue, equalNumber, epsilon) ||
                fabs(function.value(leftBorder) - function.value(rightBorder)) <= 10e-14) {
            return currentX;
        } else if (funcValue > equalNumber) {
            rightBorder = currentX;
            currentX = (leftBorder + currentX) / 2.0;
        } else {
            leftBorder = currentX;
            currentX = (rightBorder + currentX) / 2.0;
        }
    }
}

double goToLeft(double rightBorder, Function &function, double de, double e) {
    double prevShift;
    double shift = rightBorder;
    double funcValue;

    do {
        prevShift = shift;
        shift -= de * 2;
        funcValue = function.value(shift);
        de *= 2;
    } while (funcValue > 0);

    return doDichotomy(function, shift, prevShift, e, 0, 1);
}

double goToRight(double leftBorder, Function &function, double de, double e) {
    int power = 1;
    double prevShift;
    double shift = leftBorder;
    double funcValue;

    do {
        prevShift = shift;
        shift += de * 2;
        funcValue = function.value(shift);
        de *= 2;
    } while (funcValue < 0);

    return doDichotomy(function, prevShift, shift, e, 0, 1);
}

double findOnInfinityLine(double leftBorder, double rightBorder, Function &function, double de, double e) {
    double minDouble = numeric_limits<double>::min();
    double maxDouble = numeric_limits<double>::max();

    if (leftBorder == minDouble && rightBorder == maxDouble) {
        cout << "exception" << endl;
    } else if (leftBorder == minDouble) {
        return goToLeft(rightBorder, function, de, e);
    } else if (rightBorder == maxDouble) {
        return goToRight(leftBorder, function, de, e);
    }

    return 0;
}

vector<double> solveQuadEquation(QuadFunction quadFunction) {

    double discriminant = findDiscriminant(quadFunction);

    if (discriminant < 0) return vector<double>(0);

    double a = quadFunction.getA();
    double b = quadFunction.getB();

    if (discriminant == 0) {

        double root = -b / (2 * a);
        return vector<double>(1) = {root};

    } else {

        double root1 = (-b - sqrt(discriminant)) / (2 * a);
        double root2 = (-b + sqrt(discriminant)) / (2 * a);
        return vector<double>() = {root1, root2};

    }
}

vector<double> discriminantLessZeroWay(CubFunction cubFunc, double de, double e) {
    vector<double> rootList;

    double cubFuncValue = cubFunc.value(0);
    if (isInInterval(cubFuncValue, 0, e)) {
        rootList.push_back(0);
    } else if (cubFuncValue > 0) {
        double root = findOnInfinityLine(numeric_limits<double>::min(), 0, cubFunc, de, e);
        rootList.push_back(root);
    } else {
        double root = findOnInfinityLine(0, numeric_limits<double>::max(), cubFunc, de, e);
        rootList.push_back(root);
    }

    return rootList;
}

vector<double> discriminantMoreOrEqualsZeroWay(CubFunction cubFunc, QuadFunction quadFunc, double de, double e) {
    vector<double> rootList;

    vector<double> quadRootList = solveQuadEquation(quadFunc);
    if (quadRootList.size() == 0) {
        cerr << "discriminant less zero" << endl;
        throw exception();
    }

    double alpha = quadRootList[0];
    double beta = quadRootList[1];

    double minDouble = numeric_limits<double>::min();
    double maxDouble = numeric_limits<double>::max();

    double funcValueByAlpha = cubFunc.value(alpha);
    double funcValueByBeta = cubFunc.value(beta);

    vector<double> cubRootList;
    if (funcValueByAlpha > e && funcValueByBeta > e) {

        double solveOnInfToAlpha = findOnInfinityLine(minDouble, alpha, cubFunc, de, e);
        cubRootList.push_back(solveOnInfToAlpha);

    } else if (funcValueByAlpha < -e && funcValueByBeta < -e) {

        double solveOnBetaToInf = findOnInfinityLine(beta, maxDouble, cubFunc, de, e);
        cubRootList.push_back(solveOnBetaToInf);

    } else if (funcValueByAlpha > e && isInInterval(funcValueByBeta, 0, e)) {

        double solveOnInfToAlpha = findOnInfinityLine(minDouble, alpha, cubFunc, de, e);
        cubRootList.insert(cubRootList.end(), {beta, beta, solveOnInfToAlpha});

    } else if (isInInterval(funcValueByAlpha, 0, e) && funcValueByBeta < -e) {

        double solveOnBetaToInf = findOnInfinityLine(beta, maxDouble, cubFunc, de, e);
        cubRootList.insert(cubRootList.end(), {alpha, alpha, solveOnBetaToInf});

    } else if (funcValueByAlpha > e && funcValueByBeta < -e) {

        double solveOnInfToAlpha = findOnInfinityLine(minDouble, alpha, cubFunc, de, e);
        double solveOnBetaToInf = findOnInfinityLine(beta, maxDouble, cubFunc, de, e);

        double solveOnAlphaToBeta = doDichotomy(cubFunc, alpha, beta, e, 0, -1);

        cubRootList.insert(cubRootList.end(), {solveOnInfToAlpha, solveOnBetaToInf, solveOnAlphaToBeta});

    } else if (isInInterval(funcValueByAlpha, 0, e) && isInInterval(funcValueByBeta, 0, e)) {

        cubRootList.push_back((alpha + beta) / 2);

    }

    return cubRootList;
}

vector<double> solveCubEquation(Function &function, double de, double e) {
    CubFunction *cubFunc = (CubFunction *) &function;
    QuadFunction quadFunc = QuadFunction(3 * cubFunc->getA(), 2 * cubFunc->getB(), cubFunc->getC());

    double discriminant = findDiscriminant(quadFunc);
    if (discriminant < 0) {
        return discriminantLessZeroWay(*cubFunc, de, e);
    } else {
        return discriminantMoreOrEqualsZeroWay(*cubFunc, quadFunc, de, e);
    }
}

int main() {
    fstream fileIn;
    fileIn.open("dav.txt", fstream::in);
    FILE *fileOut = fopen("res.txt", "w");

    if (!fileIn.is_open() || fileOut == NULL) {
        cerr <<  "file cannot open" << endl;
        throw exception();
    }

    string line;
    double b, c, d, de, e;
    while (getline(fileIn, line)) {
        istringstream iss(line);
        iss >> b >> c >> d >> de >> e;

        CubFunction cubFunction = CubFunction(1, b, c, d);
        vector<double> rootList = solveCubEquation(cubFunction, de, e);

        fprintf(fileOut, "Equal: a = %lf, b = %lf, c = %lf, d = %lf, de = %lf, e = %lf\n", 1.0, b, c, d, de, e);
        fprintf(fileOut, "root number: %d\nroots: ", rootList.size());
        for (double root : rootList) {
            fprintf(fileOut, "%lf ", root);
        }
        fprintf(fileOut, "\nfunc value in root: ");
        for (double root : rootList) {
            fprintf(fileOut, "%lf ", abs(cubFunction.value(root)));
        }
        fprintf(fileOut, "\n\n");
    }

    fileIn.close();
    return 0;
}
