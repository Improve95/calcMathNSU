package ru.improve.dz1.functions;

import lombok.Getter;
import lombok.RequiredArgsConstructor;

import java.math.BigDecimal;

@RequiredArgsConstructor
@Getter
public class CubFunction implements Function {

    private final double a;
    private final double b;
    private final double c;
    private final double d;

    public double value(double x) {
        BigDecimal x3 = BigDecimal.valueOf(x).pow(3);

        BigDecimal x2 = BigDecimal.valueOf(x).pow(2);
        x2 = x2.multiply(new BigDecimal(b));

        BigDecimal x1 = BigDecimal.valueOf(x);
        x1 = x1.multiply(new BigDecimal(d));

        BigDecimal res = x3.add(x2);
        res = res.add(x1);

        return res.doubleValue();
    }
}
