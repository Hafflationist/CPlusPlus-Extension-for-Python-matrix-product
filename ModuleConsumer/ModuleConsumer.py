from itertools import islice
from random import random
from time import perf_counter
from TestModule import division
from TestModule import matrixMultiplication
from random import randint


COUNT = 500000  # Change this value depending on the speed of your computer
DATA = list(islice(iter(lambda: (random() - 0.5) * 3.0, None), COUNT))

e = 2.7182818284590452353602874713527

def sinh(x):
    return (1 - (e ** (-2 * x))) / (2 * (e ** -x))

def cosh(x):
    return (1 + (e ** (-2 * x))) / (2 * (e ** -x))

def tanh(x):
    tanh_x = sinh(x) / cosh(x)
    return tanh_x

def PyMatrixMultiplication(matrixA, matrixB):
    return [[sum(a * b for a,b in zip(X_row,Y_col)) for Y_col in zip(*matrixB)] for X_row in matrixA]

def test(fn, name):
    start = perf_counter()
    result = fn(DATA)
    duration = perf_counter() - start
    print('{} took {:.3f} seconds\n\n'.format(name, duration))

    for d in result:
        assert -1 <= d <= 1, " incorrect values"

def perfTest(func):
    start = perf_counter()
    func()
    duration = perf_counter() - start
    return duration

def generateGiantMatrix():
    return [[randint(0,100000000) for x in range(100)]for y in range(100)]




if __name__ == "__main__":
    print('Starting module test:')

    matrixA = [[1,2,3],
        [2,3,4]]
    matrixB = [[4,5,1],
        [5,6,1],
        [6,7,1]]

    print("Python")
    print(PyMatrixMultiplication(matrixA, matrixB))
    print("C++:")
    print(matrixMultiplication(matrixA, matrixB))

    matrixA = generateGiantMatrix()
    matrixB = generateGiantMatrix()
    
    duration = perfTest(lambda: PyMatrixMultiplication(matrixA, matrixB))
    print("Python:\t" + str(duration))

    duration = perfTest(lambda: matrixMultiplication(matrixA, matrixB))
    print("C++:\t" + str(duration))