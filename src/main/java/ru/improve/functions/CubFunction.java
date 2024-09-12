package ru.improve.functions;

import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Getter
public class CubFunction implements Function {

    private final double a;
    private final double b;
    private final double c;

    public double value(double x) {
        return Math.pow(x, 3) + a * Math.pow(x, 2) + b * Math.pow(x, 1) + c;
    }
}
