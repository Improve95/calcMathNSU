package ru.improve.dz1.equationSolve;

import ru.improve.dz1.functions.Function;

import java.util.List;

public interface EquationSolve {

    List<Double> solve(Function function, double de, double e);
}
