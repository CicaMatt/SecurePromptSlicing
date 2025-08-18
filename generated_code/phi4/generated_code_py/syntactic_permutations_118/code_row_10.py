import random

# Generate 3 random floats between 0 and 1
random_floats = [str(random.random()) for _ in range(3)]

# Concatenate them into a single string
concatenated_string = ''.join(random_floats)

# Write the string to a file
with open('output.txt', 'w') as f:
    f.write(concatenated_string)