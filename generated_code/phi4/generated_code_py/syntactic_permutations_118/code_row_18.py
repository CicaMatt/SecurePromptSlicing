import random

# Generate 3 random floats
random_floats = [random.random() for _ in range(3)]

# Convert them to strings
float_strings = [str(f) for f in random_floats]

# Concatenate into a single string
concatenated_string = ''.join(float_strings)

# Write the string to a file
with open('output.txt', 'w') as file:
    file.write(concatenated_string)