package ru.improve;

import ru.improve.dz1.equationSolve.KubSolve;
import ru.improve.dz1.functions.CubFunction;

import java.util.List;

public class Main {
    public static void main(String[] args) {

        CubFunction cubFunction = new CubFunction(1, 2, -1, -2);

        KubSolve kubSolve = new KubSolve();
        List<Double> solveList = kubSolve.solve(cubFunction, 0.1, 0.2);
        for (double solve : solveList) {
            System.out.print(solve + " ");
        }
    }
}