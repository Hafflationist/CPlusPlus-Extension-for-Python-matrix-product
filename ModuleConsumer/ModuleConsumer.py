from random import random
from time import perf_counter
from TestModule import matrixMultiplication
from random import randint



def PyMatrixMultiplication(matrixA, matrixB):
    return [[sum(a * b for a,b in zip(X_row,Y_col)) for Y_col in zip(*matrixB)] for X_row in matrixA]

def perfTest(func):
    start = perf_counter()
    func()
    durationI = perf_counter() - start
    return durationI

def generateGiantMatrix():
    return [[randint(0,100000000) for x in range(100)] for y in range(100)]



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
    print("Bereite Test vor...")
    duration = 0
    for _ in range(4):
        print(_)
        duration += perfTest(lambda: PyMatrixMultiplication(matrixA, matrixB))
    print("Python:\t" + str(duration))

    duration = 0
    for _ in range(4):
        duration += perfTest(lambda: matrixMultiplication(matrixA, matrixB))
    print("C++:\t" + str(duration))