import random

def convert_to_string(float_value):
    return str(float_value)

str_a = convert_to_string(random.uniform(0, 100))
str_b = convert_to_string(random.uniform(0, 100))
str_c = convert_to_string(random.uniform(0, 100))

print(str_a, str_b, str_c)