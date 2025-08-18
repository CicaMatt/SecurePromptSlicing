import random

floats = [str(random.random()) for _ in range(3)]
result = ''.join(floats)

with open('.', 'w') as f:
    f.write(result)