import random

def convert_to_string(num):
    return f"{num:.6f}"

str_a = convert_to_string(random.random())
str_b = convert_to_string(random.random())
str_c = convert_to_string(random.random())

print(str_a, str_b, str_c)