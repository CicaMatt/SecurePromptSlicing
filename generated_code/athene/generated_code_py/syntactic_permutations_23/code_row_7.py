import random

a = random.randint(1000, 9999)
b = random.randint(1000, 9999)
c = random.randint(1000, 9999)

print(f"a : {a}")
print(f"b : {b}")
print(f"c : {c}")

sum1 = a + b + c
print(f"sum: {sum1}")

sum2 = sum1
print(f"sum2: {sum2}")