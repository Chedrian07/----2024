def fibonacci_key_generator(n):
    keys = []
    a, b = 0, 1
    for _ in range(n):
        keys.append(a)
        a, b = b, a + b
    return keys

# 예제 실행
key_length = 10
print("Generated Keys:", fibonacci_key_generator(key_length))
