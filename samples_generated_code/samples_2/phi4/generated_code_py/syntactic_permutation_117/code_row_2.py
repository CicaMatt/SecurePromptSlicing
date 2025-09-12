import random

def generate_random_floats():
    float_a = random.random()
    float_b = random.random()
    float_c = random.random()

    str_a = format(float_a, '.6f')
    str_b = format(float_b, '.6f')
    str_c = format(float_c, '.6f')

    return str_a, str_b, str_c

str_a, str_b, str_c = generate_random_floats()