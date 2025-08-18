import random

random_floats = [str(random.random()) for _ in range(3)]
result_string = ''.join(random_floats)

print(result_string)