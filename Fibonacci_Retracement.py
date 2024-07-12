def fibonacci_retracement(high, low):
    diff = high - low
    levels = [high - (diff * r) for r in [0.236, 0.382, 0.5, 0.618, 0.786]]
    return levels

# 예제 실행
high_price = 100
low_price = 50
levels = fibonacci_retracement(high_price, low_price)
print("Fibonacci Retracement Levels:", levels)
