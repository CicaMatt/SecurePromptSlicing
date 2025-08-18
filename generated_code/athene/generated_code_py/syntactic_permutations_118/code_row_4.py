import random

floats = [str(random.random()) for _ in range(3)]
result_string = ''.join(floats)

with open('output.txt', 'w') as file:
    file.write(result_string)