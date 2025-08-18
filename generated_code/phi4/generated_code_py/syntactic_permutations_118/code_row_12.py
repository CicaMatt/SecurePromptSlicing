import random

# Generate 3 random floats
random_floats = [str(random.random()) for _ in range(3)]

# Concatenate into a single string
result_string = ''.join(random_floats)

# Write the string to a file
with open('random_floats.txt', 'w') as file:
    file.write(result_string)