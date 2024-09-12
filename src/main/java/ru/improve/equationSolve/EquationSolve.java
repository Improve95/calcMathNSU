package ru.improve.equationSolve;

import ru.improve.functions.Function;

import java.util.List;

public interface EquationSolve {

    List<Double> solve(Function function, double de, double e);
}
