package ru.improve.findTechnique;

import ru.improve.functions.Function;
import ru.improve.mathFunc.MyAbs;

public class Dichotomy {

    public double doDichotomy(Function function, double leftBorder, double rightBorder,
                              double epsilon, double equalNumber) {

        double currentX = (rightBorder - leftBorder) / 2;

        while (true) {
            double funcValue = function.value(currentX);
            if (MyAbs.inInterval(funcValue, equalNumber, epsilon)) {
                return currentX;
            } else if (funcValue > equalNumber) {
                currentX = (rightBorder - currentX) / 2;
            } else {
                currentX = (leftBorder - currentX) / 2;
            }
        }
    }
}
