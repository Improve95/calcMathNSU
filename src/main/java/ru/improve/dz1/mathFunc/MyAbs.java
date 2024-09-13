package ru.improve.dz1.mathFunc;

public class MyAbs {

    public static boolean inInterval(double value, double equal, double epsilon) {
        return (value + epsilon >= equal && value <= equal) ||
                (value - epsilon <= equal && value >= equal);
    }
}
