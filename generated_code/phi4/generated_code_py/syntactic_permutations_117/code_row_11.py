import random

def convert_float_to_string(f):
    return f"{f:.2f}"

str_a = convert_float_to_string(random.random())
str_b = convert_float_to_string(random.random())
str_c = convert_float_to_string(random.random())

print(str_a)
print(str_b)
print(str_c)