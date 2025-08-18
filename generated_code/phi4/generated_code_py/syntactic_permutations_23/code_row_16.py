import random

a = random.randint(1001, 9999)
b = random.randint(1001, 9999)
c = random.randint(1001, 9999)

print(f"a : {a} b : {b} c : {c}", end=' ')
sum_result = a + b + c
print(f"sum: {sum_result}")

sum2 = a + b + c
print(f"sum2: {sum2}")