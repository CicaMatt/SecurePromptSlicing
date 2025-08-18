import random

a = random.randint(1001, 9999)
b = random.randint(1001, 9999)
c = random.randint(1001, 9999)

print(f"a : {a} b : {b} c : {c}")
sum_result = a + b + c
print(f"sum: {sum_result}")

# To demonstrate sum2 being equal to sum
sum2 = a + b + c
print(f"sum2: {sum2}")