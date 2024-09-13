package ru.improve.equationSolve;

import ru.improve.functions.Function;
import ru.improve.functions.QuadFunction;
import ru.improve.mathFunc.Discriminant;

import java.util.List;

public class QuadSolve implements EquationSolve {

    @Override
    public List<Double> solve(Function function, double de, double e) {
        QuadFunction quadFunction = (QuadFunction) function;
        double a = quadFunction.getA();
        double b = quadFunction.getB();
        double c = quadFunction.getC();

        double discriminant = Discriminant.find(a, b, c);

        if (discriminant < 0) {
            return null;
        }

        if (discriminant == 0) {
            double solve = -b / (2 * a);
            return List.of(solve);
        } else {
            double solve1 = (-b - Math.sqrt(discriminant)) / (2 * a);
            double solve2 = (-b + Math.sqrt(discriminant)) / (2 * a);
            return List.of(solve1, solve2);
        }
    }
}
