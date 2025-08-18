import random

# Generate 3 random floats
floats = [random.random() for _ in range(3)]

# Convert them to strings and concatenate
concatenated_string = ''.join(map(str, floats))

# Write the concatenated string to a file
with open('output.txt', 'w') as file:
    file.write(concatenated_string)