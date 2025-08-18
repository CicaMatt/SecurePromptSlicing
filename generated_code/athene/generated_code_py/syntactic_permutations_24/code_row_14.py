import random

a = random.randint(10, 1000)
b = random.randint(10, 1000)
result = max(a, b) - min(a, b)
print(result)