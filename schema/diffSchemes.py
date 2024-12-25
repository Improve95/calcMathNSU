from abc import ABC, abstractmethod
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

def calculateGraphsWithAnyParameters(a, b, N12, T12, info: str, method):
    graphs = []
    for N_iter in range(1):
        N = N12[N_iter]

        for T_iter in range(1):
            T = T12[T_iter]
            h = (b - a) / float(N)

            for task_iter in range(1):
                
                multiplier = 0.0
                for kt in range(1):
                    multiplier += 0.25
                    tao = h * multiplier
                    k = T / tao

                    graphData = f"{info}: N = {N}, T = {T}, h = {h}, tao = {tao}, k = {k}"
                    xcs, ycs = method(tao, h, N, k)
                    graph = Graph(graphData, xcs, ycs)
                    graphs.append(graph)
    
    return graphs

def calculateGraph(tao, h, N, k):
    k = int(k)
    coords = np.zeros((N + 1, k))

    for j in range(N):
        coords[j][0] = Sinus.value(j * h)

    xcs, ycs = [], []
    for n in range (k - 1):
        for j in range (N):
            coords[j][n + 1] = (-1) * (tao / h) * (coords[(j + 1) % N][n] - coords[j][n % N]) + coords[j][n % N]

    for j in range(N):
        xcs.append(j * h)
        ycs.append(coords[j][k - 1])

    return xcs, ycs

def main():
    a, b = 0.0, 10.0
    N12 = [100, 1000]
    T12 = [1.0, 2.0]

    totalGraphs = []

    graphs = calculateGraphsWithAnyParameters(a, b, N12, T12, "forward - task1", calculateGraph)
    totalGraphs.append(graphs)

    drawGraphs(graphs)

if __name__ == '__main__':
    main()
    