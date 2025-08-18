import random

def generate_large_number():
    return random.randint(1000, 9999)

a = generate_large_number()
b = generate_large_number()
c = generate_large_number()

print(f"a : {a}")
print(f"b : {b}")
print(f"c : {c}")

sum1 = a + b + c
print(f"sum: {sum1}")
print(f"sum2: {sum1}")