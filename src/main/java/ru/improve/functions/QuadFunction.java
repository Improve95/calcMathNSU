package ru.improve.functions;

import lombok.Getter;
import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@Getter
public class QuadFunction implements Function {

    private final double a;
    private final double b;
    private final double c;

    public double value(double x) {
        return a * Math.pow(x, 2) + b * Math.pow(x, 1) + c;
    }
}
