from abc import ABC, abstractmethod
import numpy as np
import math
from math import sin, pow

import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

class Graphic():
    def __init__(self, data: str, coords: list):
        self.data = data
        self.coords = coords

class Function(ABC):
    @abstractmethod
    def value(x):
        pass

class Sinus(Function):
    def value(x):
        return sin(2 * math.pi * (x + 5) / 10)

class Task(ABC):
    @abstractmethod
    def task(x):
        pass

class FirstTask(Function):
    def value(x):
        return x;

def drawGraphics(graphics):
    pdf_file = "graphs.pdf"
    with PdfPages(pdf_file) as pdf:
        for graphic in graphics:
            plt.figure(figsize=(6, 4))
            plt.plot(graphic.coords, label='sin', color='blue')
            plt.title(graphic.data)
            plt.legend()
            plt.grid()
            pdf.savefig()
            plt.close()

def forwardDifference(tao, h, N, k):
    k = int(k)
    coords = np.zeros((N + 1, k + 1))

    for j in range(N):
        coords[j][0] = Sinus.value(j * h)

    for j in range (N):
        for n in range (k):
            coords[j][n + 1] = -(tao / h) * (coords[j + 1][n] - coords[j][n]) + coords[j][n]

    return coords

def main():
    a, b = 0.0, 10.0
    N12 = [100, 1000]
    T12 = [1.0, 2.0]
    graphics = []

    for N_iter in range(2):
        N = N12[N_iter]

        for T_iter in range(2):
            T = T12[T_iter]
            h = (b - a) / float(N)
            
            for task_iter in range(1):

                multiplier = 0.0
                for kt in range(4):
                    multiplier += 0.25
                    tao = h / 4 * multiplier
                    k = T / tao

                    graphicData = f"N = {N}, T = {T}, h = {h}, tao = {tao}, k = {k}"
                    coords = forwardDifference(tao, h, N, k)
                    graphic = Graphic(graphicData, coords)
                    graphics.append(graphic)

    # drawGraphics(graphics)

if __name__ == '__main__':
    main()
    