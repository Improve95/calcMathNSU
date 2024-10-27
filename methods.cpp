#include <iostream>
#include <math.h>
#include <limits>

using namespace std;

double function(double x) {
    return pow(x,2) - 5;
}

double derFunc(double x) {
    return 2*x;
}

void oneTangent(){
    double x0 = 2, x1 = 2, xn;
    cout << "x0: " <<x0 << "; " << "|x0 - sqrt(5)|: " << abs(x0 - sqrt(5)) <<  endl;
    for (int i = 1; i < 5; i++){
        xn = x1 - (function(x1) / derFunc(x0));
        printf("x%d : xn = %f; abs(x%d - sqrt): %f\n", i, xn, i,  abs(xn - sqrt(5)));
//        cout << "x" << i << ": " <<xn << "; " << "|x" << i <<" - sqrt(5)|: " << abs(xn - sqrt(5)) <<  endl;
        x1 = xn;
    }
}

void secant() {
    double x0 = 2, x1 = 2, x2 = 2.25, x3;
    cout << "x0: " <<x1 << "; " << "|x0 - sqrt(5)|: " << abs(x1 - sqrt(5)) <<  endl;
    cout << "x1: " <<x2 << "; " << "|x1 - sqrt(5)|: " << abs(x2 - sqrt(5)) <<  endl;
    for (int i = 2; i < 5; i++){
        x3 = x2 - (((x2 - x1)/(function(x2) - function(x1))) * function(x2));
        cout << "x" << i <<": "<<x3 <<"; " << "|x" <<i <<" - sqrt(5)|: " << abs(x3 - sqrt(5)) <<  endl;
//        printf("x%d: %f; abs(x%d - sqrt(5)): %f\n", i, x0, i, abs(x0 - sqrt(5)));
        x1 = x2;
        x2 = x3;
    }
}

void Newton() {
    double x0 = 2, xn;
//    cout << "x0: " <<x0 << "; " << "|x0 - sqrt(5)|: " << abs(x0 - sqrt(5)) <<  endl;
    printf("x0: %lf; abs(x0 - sqrt(5)): %lf\n", x0, abs(x0 - sqrt(5)));
    for (int i = 1; i < 5; i++){
        xn = x0 - function(x0) / derFunc(x0);
//        cout << "x" << i <<": "<<xn <<"; " << "|x" <<i <<" - sqrt(5)|: " << abs(xn - sqrt(5)) <<  endl;
        printf("x%d: %lf; abs(x%d - sqrt(5)): %lf\n", i, x0, i, abs(x0 - sqrt(5)));
        x0 = xn;
    }
}

int main() {
    cout.precision(numeric_limits<double>::digits10 + 1);

    cout << "newton" << endl;
    Newton();
    cout << endl << "one tangent" << endl;
    oneTangent();
    cout << endl << "secant" << endl;
    secant();
}