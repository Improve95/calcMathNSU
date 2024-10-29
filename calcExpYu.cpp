#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double f(double x) {
    return exp(x);
}

double trapezoidal(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.0;

    sum += f(a) + f(b);

    for (int i = 1; i < n; ++i) {
        double x_i = a + i * h;
        sum += 2 * f(x_i);
    }

    return (h / 2) * sum;
}

int main() {
    double a = 0.0, b = 1.0;

    double I_exact = exp(1) - 1;

    int n_10 = 10;
    double S_h_10 = trapezoidal(a, b, n_10);

    int n_20 = 20;
    double S_h_20 = trapezoidal(a, b, n_20);

    double error_10 = fabs(I_exact - S_h_10);
    double error_20 = fabs(I_exact - S_h_20);
    double log2_value = log2(error_10 / error_20);

    cout << "" << I_exact << endl;
    cout << "n = 10: " << S_h_10 << endl;
    cout << "n = 20: " << S_h_20 << endl;
    cout << "log2(|I - S_h| / |I - S_(h/2)|): " << log2_value << endl;

    return 0;
}