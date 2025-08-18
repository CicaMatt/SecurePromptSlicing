import random

random_floats = [str(random.random()) for _ in range(3)]
with open('random_floats.txt', 'w') as file:
    file.write('\n'.join(random_floats))