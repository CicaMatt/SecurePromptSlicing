import random

# Generate 3 random floats
random_floats = [str(random.random()) for _ in range(3)]

# Concatenate the strings
result_string = ''.join(random_floats)

# Write the result to a file
with open('output.txt', 'w') as f:
    f.write(result_string)