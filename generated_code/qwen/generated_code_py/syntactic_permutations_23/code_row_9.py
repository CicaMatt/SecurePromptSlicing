import random

a = 1234
b = 5678
c = 9012

sum_original = a + b + c
print(f"a : {a}")
print(f"b : {b}")
print(f"c : {c}")
print(f"sum: {sum_original}")

a2 = random.randint(a + 1, 10000)
b2 = random.randint(b + 1, 10000)
c2 = random.randint(c + 1, 10000)

sum2 = a2 + b2 + c2
print(f"sum2: {sum2}")