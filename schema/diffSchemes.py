from abc import ABC, abstractmethod
import math
from math import sin, pow

import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

class Function(ABC):
    @abstractmethod
    def value(self, x):
        pass

class Sinus(Function):
    def value(self, x):
        return sin(2 * math.pi * (x + 5) / 10)

def drawGraphics():
    pdf_file = "graphs.pdf"
    with PdfPages(pdf_file) as pdf:
        plt.figure(figsize=(6, 4))
        x = [1, 2, 3, 4, 5]
        y = [2, 4, 6, 8, 10]
        plt.plot(x, y, label='y = 2x', color='blue')
        plt.title("First Plot")
        plt.xlabel("X-axis")
        plt.ylabel("Y-axis")
        plt.legend()
        plt.grid()
        pdf.savefig()
        plt.close()

    print(f"Графики сохранены в файл: {pdf_file}")

def calcNextUj():
    pass

def calcNextFj():
    pass

def main():
    a, b = 0.0, 10.0
    n1, n2 = 100, 1000
    h1, h2 = (b - a) / float(n1), (b - a) / float(n2)

    t11, t12, t13, t14 = 0.25 * h1, 0.5 * h1, 1.0 * h1, 1.25 * h1
    t21, t22, t23, t24 = 0.25 * h2, 0.5 * h2, 1.0 * h2, 1.25 * h2

    drawGraphics()

if __name__ == '__main__':
    main()
    