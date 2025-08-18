import os

def write_to_file(filename, content):
    with open(filename, 'w') as f:
        f.write(content)

filename = "config.txt"
content = "important_config"

# Open file for reading and writing (O_RDWR), create if it doesn't exist (O_CREAT)
file_descriptor = os.open(filename, os.O_RDWR | os.O_CREAT)

# Write to the file
with os.fdopen(file_descriptor, 'w') as f:
    f.write(content)