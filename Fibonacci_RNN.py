import numpy as np
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import SimpleRNN, Dense

# 피보나치 수열 생성
def fibonacci_sequence(n):
    fib = [0, 1]
    for i in range(2, n):
        fib.append(fib[i-1] + fib[i-2])
    return fib

# 데이터 전처리
n = 20
sequence = fibonacci_sequence(n)
X = np.array(sequence[:-1]).reshape((1, n-1, 1))
y = np.array(sequence[1:]).reshape((1, n-1, 1))

# RNN 모델 정의
model = Sequential()
model.add(SimpleRNN(10, input_shape=(n-1, 1)))
model.add(Dense(1))

model.compile(optimizer='adam', loss='mse')
model.fit(X, y, epochs=100, verbose=0)

# 예측
prediction = model.predict(X)
print("Fibonacci Sequence Prediction:", prediction.flatten())
