package ru.improve.equationSolve;

import ru.improve.functions.Function;
import ru.improve.mathFunc.Discriminant;
import ru.improve.findTechnique.FindEqualSolveOnInfinityLine;
import ru.improve.functions.CubFunction;
import ru.improve.functions.QuadFunction;

import java.util.ArrayList;
import java.util.List;

public class KubSolve implements EquationSolve {

    private List<Double> discriminantLessZeroWay(CubFunction cubFunc, double de, double e) {
        List<Double> solveNumber = new ArrayList<>();
        FindEqualSolveOnInfinityLine findSolve = new FindEqualSolveOnInfinityLine();

        double cubFuncValue = cubFunc.value(0);
        if (cubFuncValue == 0) {
            solveNumber.add((double) 0);
        } else if (cubFuncValue > 0) {
            findSolve.find(Double.MIN_VALUE, 0, cubFunc, de, e);
        } else {
            findSolve.find(0, Double.MAX_VALUE, cubFunc, de, e);
        }

        return solveNumber;
    }

    private List<Double> discriminantMoreOrEqualsZeroWay(CubFunction cubFunc, QuadFunction quadFunc, double de, double e) {
        List<Double> solveNumber = new ArrayList<>();

        EquationSolve quadSolve = new QuadSolve();
        List<Double> quadSolveList = quadSolve.solve(quadFunc, de, e);

        double alpha = quadSolveList.get(0);
        double beta = quadSolveList.get(1);

        FindEqualSolveOnInfinityLine findSolve = new FindEqualSolveOnInfinityLine();

        double solveOnInfToAlpha = findSolve.find(Double.MIN_VALUE, alpha, cubFunc, de, e);
        double solveOnBetaToInf = findSolve.find(beta, Double.MAX_VALUE, cubFunc, de, e);

        return solveNumber;
    }

    /*private List<Double> way1(CubFunction cubFunc, double de, double e, double alpha, double beta) {
        return null;
    }
    private List<Double> way2() {
        return null;
    }
    private List<Double> way3() {
        return null;
    }
    private List<Double> way4() {
        return null;
    }
    private List<Double> way5() {
        return null;
    }*/

    public List<Double> solve(Function function, double de, double e) {
        CubFunction cubFunction = (CubFunction) function;
        double a = cubFunction.getA();
        double b = cubFunction.getB();
        double c = cubFunction.getC();

        CubFunction cubFunc = new CubFunction(a, b, c);
        QuadFunction quadFunc = new QuadFunction(1, b - 1, c - 1);

        double discriminant = Discriminant.find(quadFunc);
        if (discriminant < 0) {
            return discriminantLessZeroWay(cubFunc, de, e);
        } else {
            return discriminantMoreOrEqualsZeroWay(cubFunc, quadFunc, de, e);
        }
    }
}
