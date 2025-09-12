import random

a = int(input("Enter integer for a: "))
b = int(input("Enter integer for b: "))
c = int(input("Enter integer for c: "))

random_a = a + random.randint(1, 10000)
random_b = b + random.randint(1, 10000)
random_c = c + random.randint(1, 10000)

sum_original = a + b + c
sum_with_randoms = random_a + random_b + random_c

print(f"a : {a} b : {b} c : {c} sum: {sum_original} sum2: {sum_with_randoms}")