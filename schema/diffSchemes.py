import numpy as np
import math
from math import sin, pow

import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

class Graph():
    def __init__(self, info: str, xCoords: list, yCoords: list):
        self.info = info
        self.xCoords = xCoords
        self.yCoords = yCoords

class Sinus():
    def value(x):
        return sin(2 * math.pi * (x + 5) / 10) + 3

def drawGraphs(graphs):
    pdf_file = "graphs.pdf"
    with PdfPages(pdf_file) as pdf:
        for graph in graphs:
            plt.figure(figsize=(6, 4))
            plt.plot(graph.xCoords, graph.yCoords, label='sin', color='blue')
            plt.title(graph.info)
            plt.legend()
            plt.grid()
            pdf.savefig()
            plt.close()

def forwardTask1(j, n, tao, h, N, coords):
    return (-1) * (tao / h) * (coords[(j + 1) % N][n] - coords[j][n]) + coords[j][n]

def forwardTask2(j, n, tao, h, N, coords):
    return (-1) * (tao / h) * (pow(coords[(j + 1) % N][n], 2) / 2 - pow(coords[j][n], 2) / 2) + coords[j][n]

def godunovTask1(j, n, tao, h, N, coords):
    return (-1) * (tao / h) * (coords[j][n] - coords[(j - 1) % N][n]) + coords[j][n]

def godunovTask2(j, n, tao, h, N, coords):
    return (-1) * (tao / h) * (pow(coords[j][n], 2) / 2 - pow(coords[(j - 1) % N][n], 2) / 2) + coords[j][n]


def calcWj_t1(j, n, N, cs):
    return cs[(j + 2) % N][n] - 4 * cs[(j + 1) % N][n] + 6 * cs[j % N][n] - 4 * cs[(j - 1) % N][n] + cs[(j - 2) % N][n]

def calcF12_t1(j, n, r, N, cs):
    return (cs[j % N][n] + cs[(j + 1) % N][n]) / 2 - r / 3 * (cs[(j + 1) % N][n] - cs[j % N][n])

def calcF2_t1(j, n, r, N, cs):
    return cs[j % N][n] - 2 * r / 3 * (calcF12_t1(j, n, r, N, cs) - calcF12_t1(j - 1, n, r, N, cs))

def rusanovTask1(j, n, tao, h, N, cs):
    r = tao / h
    return cs[j][n] - r / 24.0 * (7 * (cs[(j + 1) % N][n] - cs[(j - 1) % N][n]) - 2 * (cs[(j + 2) % N][n] - cs[(j - 2) % N][n])) \
            - 3 / 8 * r * (calcF12_t1(j + 1, n, r, N, cs) - calcF12_t1(j - 1, n, r, N, cs)) - 0.104 * calcWj_t1(j, n, N, cs)

def calcWj_t2(j, n, N, cs):
    return cs[(j + 2) % N][n] - 4 * cs[(j + 1) % N][n] + 6 * cs[j % N][n] - 4 * cs[(j - 1) % N][n] + cs[(j - 2) % N][n]

def calcF12_t2(j, n, r, N, cs):
    return (cs[j % N][n] + cs[(j + 1) % N][n]) / 2 - r / 3 * (pow(cs[(j + 1) % N][n], 2) / 2 - pow(cs[j % N][n], 2) / 2)

def calcF2_t2(j, n, r, N, cs):
    return cs[j % N][n] - 2 * r / 3 * (pow(calcF12_t2(j, n, r, N, cs), 2) / 2 - pow(calcF12_t2(j - 1, n, r, N, cs), 2) / 2)

def rusanovTask2(j, n, tao, h, N, cs):
    r = tao / h
    return cs[j][n] - r / 24.0 * (7 * (pow(cs[(j + 1) % N][n], 2) / 2 - pow(cs[(j - 1) % N][n], 2) / 2) - 2 * (pow(cs[(j + 2) % N][n], 2) / 2 - pow(cs[(j - 2) % N][n], 2) / 2)) \
            - 3 / 8 * r * (pow(calcF12_t2(j + 1, n, r, N, cs), 2) / 2 - pow(calcF12_t2(j - 1, n, r, N, cs), 2) / 2) - 0.104 * calcWj_t2(j, n, N, cs)

def calculateGraphs(tao, h, N, k, method):
    k = int(k)
    coords = np.zeros((N + 1, k))

    for j in range(N):
        coords[j][0] = Sinus.value(j * h)

    xcs, ycs = [], []
    for n in range (k - 1):
        for j in range (N):
            try:
                res = method(j, n, tao, h, N, coords)
            except OverflowError:
                res = float('inf')
                # for j in range(N):
                    # xcs.append(j * h)
                    # ycs.append(coords[j][k - 1])
                    # return xcs, ycs
                
            coords[j][n + 1] = res

    return xcs, ycs

def calculateGraphsWithAnyParameters(a, b, N12, T12, info: str, method):
    graphs = []
    for N_iter in range(1):
        N = N12[N_iter]

        for T_iter in range(2):
            T = T12[T_iter]
            h = (b - a) / float(N)
            multiplier = 0.0

            for kt in range(4):
                multiplier += 0.25
                tao = h * multiplier
                k = T / tao

                graphData = f"{info}: N = {N}, T = {T}, h = {h}, tao = {round(tao, 4)}, k = {round(k, 4)}"
                xcs, ycs = calculateGraphs(tao, h, N, k, method)
                graph = Graph(graphData, xcs, ycs)
                graphs.append(graph)
    
    return graphs

def main():
    a, b = 0.0, 10.0
    N12 = [100, 1000]
    T12 = [1.0, 2.0]

    totalGraphs = []

    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "forward-t1", forwardTask1)
    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "forward-t2", forwardTask2)
    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, [0.22, 0.25], "forward-t2", forwardTask2)

    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "godunov-t1", godunovTask1)
    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "godunov-t2", godunovTask2)

    totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "rusanov-t1", rusanovTask1)
    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "rusanov-t2", rusanovTask2)

    drawGraphs(totalGraphs)

if __name__ == '__main__':
    main()
    