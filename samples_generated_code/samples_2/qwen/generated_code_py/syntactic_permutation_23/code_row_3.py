import random

a = 1234
b = 5678
c = 9012

sum_original = a + b + c
sum_random = (random.randint(a+1, 10000)) + (random.randint(b+1, 10000)) + (random.randint(c+1, 10000))

print(f"a : {a}")
print(f"b : {b}")
print(f"c : {c}")
print(f"sum: {sum_original}")
print(f"sum2: {sum_random}")