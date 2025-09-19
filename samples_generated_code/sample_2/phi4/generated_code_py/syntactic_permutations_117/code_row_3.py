import random

def float_to_string(value):
    return f"{value:.6f}"

str_a = float_to_string(random.random())
str_b = float_to_string(random.random())
str_c = float_to_string(random.random())

print(str_a)
print(str_b)
print(str_c)