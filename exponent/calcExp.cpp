#include <iostream>
#include <cmath>

using namespace std;

double func(double x) {
    return exp(x);
}

double evaluate_integral(int n, double a, double b) {
    double result = 0;
    double h = (b - a) / n;
    for (int i = 0; i < n; ++i) {
        result += (func(h * i) + func(h * (i + 1))) * h / 2;
    }
    return result;
}

int main() {
    double I = M_E - 1;
    cout << "1) " << endl;
    cout << "I: " << I << "\n";

    cout << endl << "2)" << endl;

    cout << "n = 10, 20:\n";
    double result1 = evaluate_integral(10, 0, 1);
    cout << "S_h: " << result1 << "\n";

    double result2 = evaluate_integral(20, 0, 1);
    cout << "S_(h/2): " << result2 << "\n";
    cout << "k: " << log2(fabs(I - result1) / fabs(I - result2)) << "\n";

    cout << endl << "3)" << endl;

    cout << "n = 100, 200:\n";
    double result3 = evaluate_integral(100, 0, 1);
    cout << "S_h: " << result3 << "\n";

    double result4 = evaluate_integral(200, 0, 1);
    cout << "S_(h/2): " << result4 << "\n";
    cout << "k: " << log2(fabs(I - result3) / fabs(I - result4)) << "\n";

    return 0;
}
