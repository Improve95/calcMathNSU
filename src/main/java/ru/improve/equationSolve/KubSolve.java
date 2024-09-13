package ru.improve.equationSolve;

import ru.improve.findTechnique.Dichotomy;
import ru.improve.functions.Function;
import ru.improve.mathFunc.Discriminant;
import ru.improve.findTechnique.FindEqualSolveOnInfinityLine;
import ru.improve.functions.CubFunction;
import ru.improve.functions.QuadFunction;
import ru.improve.mathFunc.MyAbs;

import java.util.ArrayList;
import java.util.List;

public class KubSolve implements EquationSolve {

    public List<Double> solve(Function function, double de, double e) {
        CubFunction cubFunc = (CubFunction) function;

        QuadFunction quadFunc = new QuadFunction(3, cubFunc.getB() * 2, cubFunc.getC());

        double discriminant = Discriminant.find(quadFunc);
        if (discriminant < 0) {
            return discriminantLessZeroWay(cubFunc, de, e);
        } else {
            return discriminantMoreOrEqualsZeroWay(cubFunc, quadFunc, de, e);
        }
    }

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

        double funcValueByAlpha = cubFunc.value(alpha);
        double funcValueByBeta = cubFunc.value(beta);
        if (funcValueByAlpha > e && funcValueByBeta > e) {

            double solveOnInfToAlpha = findSolve.find(Double.MIN_VALUE, alpha, cubFunc, de, e);
            solveNumber.add(solveOnInfToAlpha);

        } else if (funcValueByAlpha < -e && funcValueByBeta < -e) {

            double solveOnBetaToInf = findSolve.find(beta, Double.MAX_VALUE, cubFunc, de, e);
            solveNumber.add(solveOnBetaToInf);

        } else if (funcValueByAlpha > e && MyAbs.inInterval(funcValueByAlpha, 0, e)) {

            double solveOnInfToAlpha = findSolve.find(Double.MIN_VALUE, alpha, cubFunc, de, e);
            solveNumber.addAll(List.of(beta, beta, solveOnInfToAlpha));

        } else if (MyAbs.inInterval(funcValueByAlpha, 0, e) && funcValueByBeta < -e) {

            double solveOnBetaToInf = findSolve.find(beta, Double.MAX_VALUE, cubFunc, de, e);
            solveNumber.addAll(List.of(alpha, alpha, solveOnBetaToInf));

        } else if (funcValueByAlpha > e && funcValueByBeta < -e) {

            double solveOnInfToAlpha = findSolve.find(Double.MIN_VALUE, alpha, cubFunc, de, e);
            double solveOnBetaToInf = findSolve.find(beta, Double.MAX_VALUE, cubFunc, de, e);

            Dichotomy dichotomy = new Dichotomy();
            double solveOnAlphaToBeta = dichotomy.doDichotomy(cubFunc, alpha, beta, e, 0, false);

            solveNumber.addAll(List.of(solveOnInfToAlpha, solveOnBetaToInf, solveOnAlphaToBeta));

        } else {

            solveNumber.add((alpha + beta) / 2);

        }

        return solveNumber;
    }
}
