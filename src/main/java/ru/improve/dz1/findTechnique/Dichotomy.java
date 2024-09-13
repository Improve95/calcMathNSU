package ru.improve.dz1.findTechnique;

import ru.improve.dz1.functions.Function;
import ru.improve.dz1.mathFunc.MyAbs;

public class Dichotomy {

    public double doDichotomy(Function function, double leftBorder, double rightBorder,
                              double epsilon, double equalNumber, boolean functionIsIncrease) {

        double reverseFuncValue = 1;
        if (!functionIsIncrease) {
            reverseFuncValue = -1;
        }

        double currentX = (rightBorder + leftBorder) / 2;

        while (true) {
            double funcValue = function.value(currentX) * reverseFuncValue;
            if (MyAbs.inInterval(funcValue, equalNumber, epsilon)) {
                return currentX;
            } else if (funcValue > equalNumber) {
                currentX = (leftBorder + currentX) / 2;
            } else {
                currentX = (rightBorder + currentX) / 2;
            }
        }
    }
}
