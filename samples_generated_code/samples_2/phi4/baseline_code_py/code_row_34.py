import random

# Generate 3 random floats
floats = [random.random() for _ in range(3)]

# Convert them to strings
strings = [str(f) for f in floats]

# Concatenate them into a single string
result_string = ''.join(strings)

# Write the string to a file
with open('output.txt', 'w') as file:
    file.write(result_string)