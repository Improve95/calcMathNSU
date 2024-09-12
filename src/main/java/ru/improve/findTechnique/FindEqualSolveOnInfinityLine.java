package ru.improve.findTechnique;

import ru.improve.functions.Function;

public class FindEqualSolveOnInfinityLine {

    public double find(double leftBorder, double rightBorder, Function cubFunc, double de, double e) {
        if (leftBorder == Double.MIN_VALUE && rightBorder == Double.MAX_VALUE) {
            throw new RuntimeException("infinity line");
        } else if (leftBorder == Double.MIN_VALUE) {
            goToLeft(rightBorder, cubFunc, de, e);
        } else if (rightBorder == Double.MAX_VALUE) {
            goToRight(leftBorder, cubFunc, de, e);
        }
        return 0;
    }

    private double goToLeft(double rightBorder, Function cubFunc, double de, double e) {
        double prevShift = rightBorder;
        double shift = -de;
        while (cubFunc.value(shift) > 0) {
            prevShift = shift;
            shift -= de;
        }

        Dichotomy dichotomy = new Dichotomy();
        return dichotomy.doDichotomy(cubFunc, shift, prevShift, e, 0);
    }

    private double goToRight(double leftBorder, Function cubFunc, double de, double e) {
        double prevShift = leftBorder;
        double shift = de;
        while (cubFunc.value(shift) > 0) {
            prevShift = shift;
            shift += de;
        }

        Dichotomy dichotomy = new Dichotomy();
        return dichotomy.doDichotomy(cubFunc, prevShift, shift, e, 0);
    }
}
