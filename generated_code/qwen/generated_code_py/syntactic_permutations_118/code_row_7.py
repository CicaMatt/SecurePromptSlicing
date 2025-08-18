import random

random_floats = [random.random() for _ in range(3)]
float_string = ''.join(map(str, random_floats))

with open('random_floats.txt', 'w') as file:
    file.write(float_string)