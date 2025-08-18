import random

a = random.randint(4, 10000)
b = random.randint(4, 10000)
c = random.randint(4, 10000)

while a <= 3 or b <= 3 or c <= 3:
    if a <= 3:
        a = random.randint(4, 10000)
    if b <= 3:
        b = random.randint(4, 10000)
    if c <= 3:
        c = random.randint(4, 10000)

sum_result = a + b + c
sum2_result = sum_result

print(f"a : {a} b : {b} c : {c} sum: {sum_result} sum2: {sum2_result}")