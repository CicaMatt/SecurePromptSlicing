import random

def float_to_str(f):
    return f"{f:.6f}"

str_a = float_to_str(random.random())
str_b = float_to_str(random.random())
str_c = float_to_str(random.random())

print(str_a)
print(str_b)
print(str_c)