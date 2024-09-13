package ru.improve;

import ru.improve.dz1.equationSolve.KubSolve;
import ru.improve.dz1.functions.CubFunction;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) {
        try (InputStream inputStream = Main.class.getResourceAsStream("dav.txt");
             BufferedReader br = new BufferedReader(new InputStreamReader(inputStream))) {

            KubSolve kubSolve = new KubSolve();

            String line;
            for (int i = 0; i < 25; i++) {
                line = br.readLine();

                List<Double> doubleList = Arrays.stream(line.split(" "))
                        .map(str -> Double.parseDouble(str))
                        .collect(Collectors.toList());

                CubFunction cubFunction = new CubFunction(1, doubleList.get(0), doubleList.get(1), doubleList.get(2));
                List<Double> solveList = kubSolve.solve(cubFunction, doubleList.get(3), doubleList.get(4));

                System.out.print(solveList.size());
                for (double solve : solveList) {
                    System.out.print(" " + solve);
                }
                System.out.println();
            }

        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }
}