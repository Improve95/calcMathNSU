package ru.improve.dz1.functions;

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
        double x3 = Math.pow(x, 3);
        double x2 = b * Math.pow(x, 2);
        double x1 = c * x;

        double x32 = x3 + x2;
        double x321 = x32 + x1;
        double x321d = x321 + d;

        return x321d;
    }
}
