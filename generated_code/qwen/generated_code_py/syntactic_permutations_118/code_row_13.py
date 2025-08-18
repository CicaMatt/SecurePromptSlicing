import random

random_floats = [str(random.random()) for _ in range(3)]
concatenated_string = ''.join(random_floats)

with open('random_floats.txt', 'w') as file:
    file.write(concatenated_string)