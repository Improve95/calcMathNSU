package ru.improve.mathFunc;

import ru.improve.functions.QuadFunction;

public class Discriminant {

    public static double find(double a, double b, double c) {
        return calculationDiscriminant(a, b, c);
    }

    public static double find(QuadFunction quadFunction) {
        double a = quadFunction.getA();
        double b = quadFunction.getB();
        double c = quadFunction.getC();
        return calculationDiscriminant(a, b, c);
    }

    private static double calculationDiscriminant(double a, double b, double c) {
        return b * b - 4 * a * c;
    }
}
