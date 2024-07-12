# 재귀를 이용한 피보나치 수 계산
def fibonacci_recursive(n):
    if n <= 1:
        return n
    else:
        return fibonacci_recursive(n-1) + fibonacci_recursive(n-2)

# 동적 계획법을 이용한 피보나치 수 계산
def fibonacci_dynamic(n):
    fib = [0, 1]
    for i in range(2, n+1):
        fib.append(fib[i-1] + fib[i-2])
    return fib[n]

# 예제 실행
print("Recursive:", fibonacci_recursive(250))
print("Dynamic:", fibonacci_dynamic(250))
