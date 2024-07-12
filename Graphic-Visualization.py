import matplotlib.pyplot as plt
import numpy as np

def fibonacci_spiral(n):
    fib = [0, 1]
    for i in range(2, n):
        fib.append(fib[i-1] + fib[i-2])

    angles = np.linspace(0, 4*np.pi, n)
    radii = fib[:n]

    x = radii * np.cos(angles)
    y = radii * np.sin(angles)

    plt.figure(figsize=(6, 6))
    plt.plot(x, y, marker='o')
    plt.title("Fibonacci Spiral")
    plt.show()

# 예제 실행
fibonacci_spiral(20)
