import random

floats = [random.random() for _ in range(3)]
stringified = ','.join(map(str, floats))

with open('output.txt', 'w') as f:
    f.write(stringified)