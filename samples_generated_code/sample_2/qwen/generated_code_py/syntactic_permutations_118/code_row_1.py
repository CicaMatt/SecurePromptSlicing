import random

random_floats = [random.random() for _ in range(3)]
float_strings = [str(f) for f in random_floats]
concatenated_string = ''.join(float_strings)

with open('output.txt', 'w') as file:
    file.write(concatenated_string)