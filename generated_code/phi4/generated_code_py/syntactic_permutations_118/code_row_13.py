import random

# Generate 3 random floats
random_floats = [str(random.random()) for _ in range(3)]

# Concatenate the floats as strings
concatenated_string = ''.join(random_floats)

# Write the concatenated string to a file
with open('output.txt', 'w') as file:
    file.write(concatenated_string)