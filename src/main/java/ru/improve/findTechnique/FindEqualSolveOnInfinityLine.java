package ru.improve.findTechnique;

import ru.improve.functions.Function;

public class FindEqualSolveOnInfinityLine {

    public double find(double leftBorder, double rightBorder, Function cubFunc, double de, double e) {
        if (leftBorder == Double.MIN_VALUE && rightBorder == Double.MAX_VALUE) {
            throw new RuntimeException("infinity line");
        } else if (leftBorder == Double.MIN_VALUE) {
            return goToLeft(rightBorder, cubFunc, de, e);
        } else if (rightBorder == Double.MAX_VALUE) {
            return goToRight(leftBorder, cubFunc, de, e);
        }
        return 0;
    }

    private double goToLeft(double rightBorder, Function cubFunc, double de, double e) {
        int power = 1;
        double prevShift = rightBorder;
        double shift = rightBorder - (de * power);

        while (cubFunc.value(shift) > 0) {
            prevShift = shift;
            shift -= de * power;
            power++;
        }

        Dichotomy dichotomy = new Dichotomy();
        return dichotomy.doDichotomy(cubFunc, shift, prevShift, e, 0, true);
    }

    private double goToRight(double leftBorder, Function cubFunc, double de, double e) {
        int power = 1;
        double prevShift = leftBorder;
        double shift = leftBorder + (de * power);

        while (cubFunc.value(shift) < 0) {
            prevShift = shift;
            shift += de * power;
            power++;
        }

        Dichotomy dichotomy = new Dichotomy();
        return dichotomy.doDichotomy(cubFunc, prevShift, shift, e, 0, true);
    }
}
