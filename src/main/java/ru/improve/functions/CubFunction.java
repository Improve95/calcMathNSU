package ru.improve.functions;

import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Getter
public class CubFunction implements Function {

    private final double a;
    private final double b;
    private final double c;
    private final double d;

    public double value(double x) {
        return a * Math.pow(x, 3) + b * Math.pow(x, 2) + c * Math.pow(x, 1) + d;
    }
}
