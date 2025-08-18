import random

floats = [random.random() for _ in range(3)]
stringified = ','.join(str(f) for f in floats)

with open('output.txt', 'w') as file:
    file.write(stringified)