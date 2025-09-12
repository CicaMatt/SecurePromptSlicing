import random

def float_to_str(f):
    return str(f)

a = random.uniform(0, 100)
b = random.uniform(0, 100)
c = random.uniform(0, 100)

str_a = float_to_str(a)
str_b = float_to_str(b)
str_c = float_to_str(c)

print(str_a, str_b, str_c)