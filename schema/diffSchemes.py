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

def calcRusanovTask1(tao, h, N, k):
    k = int(k)
    cs = np.zeros((N + 1, k))

    r = tao / h

    xcs, ycs = [], []
    f12, f2, w = np.zeros((N + 1, k)), np.zeros((N + 1, k)), np.zeros((N + 1, k))

    for j in range (N + 1):
        cs[j][0] = Sinus.value(j * h)
    
    for n in range (k - 1):
        for j in range (N + 1): 
            f12[j][n] = (cs[j][n] + cs[(j + 1) % N][n]) / 2 - r / 3 * (cs[(j + 1) % N][n] - cs[j][n])
        
        for j in range (N + 1): 
            f2[j][n] = cs[j][n] - 2 * r / 3 * (f12[j][n] - f12[(j - 1) % N][n])
        
        for j in range (N + 1): 
            w[j][n] = cs[(j + 2) % N][n] - 4 * cs[(j + 1) % N][n] + 6 * cs[j][n] - 4 * cs[(j - 1) % N][n] + cs[(j - 2) % N][n]
        
        for j in range (N + 1): 
            cs[j][n + 1] = cs[j][n] - r / 24 * (7 * (cs[(j + 1) % N][n] - cs[(j - 1) % N][n]) - 2 * (cs[(j + 2) % N][n] - cs[(j - 2) % N][n])) \
            - 3 * r / 8 * (f2[(j + 1) % N][n] - f2[(j - 1) % N][n]) - 0.104 * w[j][n]

    for j in range(N):
        xcs.append(j * h)
        ycs.append(cs[j][k - 1])

    return xcs, ycs

def calcRusanovTask2(tao, h, N, k):
    k = int(k)
    cs = np.zeros((N + 1, k))

    r = tao / h

    xcs, ycs = [], []
    f12, f2, w = np.zeros((N + 1, k)), np.zeros((N + 1, k)), np.zeros((N + 1, k))

    for j in range (N + 1):
        cs[j][0] = Sinus.value(j * h)
    
    for n in range (k - 1):
        for j in range (N + 1): 
            f12[j][n] = (cs[j][n] + cs[(j + 1) % N][n]) / 2 - r / 3 * (pow(cs[(j + 1) % N][n], 2) / 2 - pow(cs[j][n], 2) / 2)
        
        for j in range (N + 1): 
            f2[j][n] = cs[j][n] - 2 * r / 3 * (pow(f12[j][n], 2) / 2 - pow(f12[(j - 1) % N][n], 2) / 2)
        
        for j in range (N + 1): 
            w[j][n] = cs[(j + 2) % N][n] - 4 * cs[(j + 1) % N][n] + 6 * cs[j][n] - 4 * cs[(j - 1) % N][n] + cs[(j - 2) % N][n]
        
        for j in range (N + 1): 
            cs[j][n + 1] = cs[j][n] - r / 24 * (7 * (pow(cs[(j + 1) % N][n], 2) / 2 - pow(cs[(j - 1) % N][n], 2) / 2) - 2 * (pow(cs[(j + 2) % N][n], 2) / 2 - pow(cs[(j - 2) % N][n], 2) / 2)) \
            - 3 * r / 8 * (pow(f2[(j + 1) % N][n], 2) / 2 - pow(f2[(j - 1) % N][n], 2) / 2) - 0.104 * w[j][n]

    for j in range(N):
        xcs.append(j * h)
        ycs.append(cs[j][k - 1])

    return xcs, ycs

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
                return xcs, ycs
                
            coords[j][n + 1] = res

    for j in range(N):
        xcs.append(j * h)
        ycs.append(coords[j][k - 1])

    return xcs, ycs

def calculateGraphsWithAnyParameters(a, b, N12, T12, info: str, task, method):
    graphs = []
    for N in N12:
        for T in T12:
            h = (b - a) / float(N)
            multiplier = 0.25

            for multiplier in [0.25, 0.5, 1.0, 1.25]:
                if (task == 1):
                    tao = h * multiplier
                else:
                    tao = h * multiplier / 4
                k = T / tao

                graphData = f"info: N={N}, T={T}, h=h, tao={round(tao, 6)}, k={round(k, 2)}"
                xcs, ycs = calculateGraphs(tao, h, N, k, method)
                graph = Graph(graphData, xcs, ycs)
                graphs.append(graph)
                multiplier += 0.25
    
    return graphs

def calculateRusanovGraphsWithAnyParameters(a, b, N12, T12, info: str, task, rusanovTaskFunc):
    graphs = []
    for N in N12:
        for T in T12:
            h = (b - a) / float(N)
            multiplier = 0.25

            for multiplier in [0.25, 0.5, 1.0, 1.25]:
                if (task == 1):
                    tao = h * multiplier
                else:
                    tao = h * multiplier / 4
                k = T / tao

                graphData = f"{info}: N={N}, T={T}, h={h}, tao={round(tao, 6)}, k={round(k, 2)}"
                xcs, ycs = rusanovTaskFunc(tao, h, N, k)
                graph = Graph(graphData, xcs, ycs)
                graphs.append(graph)
                multiplier += 0.25
    
    return graphs

def main():
    a, b = 0.0, 10.0
    N12 = [100, 1000]
    T12 = [1.0, 2.0]

    totalGraphs = []

    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "forward-t1", 1, forwardTask1)
    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, [0.22, 0.25], "forward-t2", 2, forwardTask2)

    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "godunov-t1", 1, godunovTask1)
    # totalGraphs += calculateGraphsWithAnyParameters(a, b, N12, T12, "godunov-t2", 2, godunovTask2)

    totalGraphs += calculateRusanovGraphsWithAnyParameters(a, b, N12, T12, "rusanov-t1", 1, calcRusanovTask1)
    totalGraphs += calculateRusanovGraphsWithAnyParameters(a, b, N12, T12, "rusanov-t2", 2, calcRusanovTask2)

    drawGraphs(totalGraphs)

if __name__ == '__main__':
    main()
    