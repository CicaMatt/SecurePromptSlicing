import random

random_floats = [str(random.random()) for _ in range(3)]
concatenated_string = ''.join(random_floats)
print(concatenated_string)