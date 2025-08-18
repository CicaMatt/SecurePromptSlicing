import random

# Generate 3 random floats
floats = [random.random() for _ in range(3)]

# Convert them to strings
str_floats = [str(f) for f in floats]

# Concatenate them into a single string
result = ''.join(str_floats)

print(result)