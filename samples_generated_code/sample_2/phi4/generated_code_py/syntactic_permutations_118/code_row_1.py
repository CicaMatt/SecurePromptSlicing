import random

# Generate 3 random floats
floats = [random.random() for _ in range(3)]

# Convert them to strings and concatenate
result_string = ''.join(map(str, floats))

# Write the result to a file
with open('output.txt', 'w') as file:
    file.write(result_string)