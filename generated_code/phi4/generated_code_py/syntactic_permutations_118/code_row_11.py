import random

def generate_and_write_random_floats(filename):
    # Generate 3 random floats
    random_floats = [random.random() for _ in range(3)]
    
    # Convert them to strings
    float_strings = map(str, random_floats)
    
    # Write the string to a file
    with open(filename, 'w') as f:
        for item in float_strings:
            f.write("%s\n" % item)

# Usage example: generate_and_write_random_floats('random_floats.txt')
generate_and_write_random_floats('random_floats.txt')