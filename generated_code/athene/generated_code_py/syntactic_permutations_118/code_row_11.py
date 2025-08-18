import random

floats = [str(random.uniform(0, 1)) for _ in range(3)]
with open('output.txt', 'w') as f:
    f.write(','.join(floats))